#include <GL/glew.h>
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Mesh.h"
#include "Chunk.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

int main(void)
{
	{
		Window window = Window(WindowProps());
		glfwSetInputMode(window.GetWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		Chunk chunks;

		Shader shader("res/shaders/Basic.shader");

		shader.SetVec3("lightDir", glm::vec3(-0.5f, -0.9f, 0.3f));

		Camera cam(
			glm::vec3(0, 60, 5),
			glm::vec3(0, 0, -1),
			glm::vec3(0, 1, 0)
		);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 500.0f);
		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 mvp = projection * cam.GetViewMatrix() * model;

		glEnable(GL_DEPTH_TEST);
		glfwSwapInterval(0); //Disable vsync

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glCullFace(GL_BACK);
		glEnable(GL_CULL_FACE);
		while (window.IsRunning())
		{
			//rotate cube
			//model = glm::rotate(model, glm::radians(-0.01f), glm::vec3(1, 0.5f, 1));
			shader.Bind();
			glm::mat4 mvp = projection * cam.GetViewMatrix() * model;
			shader.SetMat4("mvp", mvp);
			shader.SetMat4("model", model);

			/*Render*/
			glClearColor(0.5f, 0.5f, 0.5f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			chunks.mesh.Draw();

			window.OnUpdate();
			cam.ProcessInput(window.GetWindow());
		}
	}

	glfwTerminate();

	return 0;
}