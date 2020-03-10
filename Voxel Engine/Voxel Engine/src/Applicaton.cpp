#include <GL/glew.h>
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

int main(void)
{
	{
		Window window = Window(WindowProps());

		float positions[12]{
			0.0f, 0.0f, -10.0f,
			1.0f, 0.0f, -10.0f,
			1.0f, 1.0f, -10.0f,
			0.0f, 1.0f, -10.0f
		};

		unsigned int indices[6]{
			0, 1, 2,
			0, 2, 3
		};

		VertexBuffer vbo(positions, 12 * sizeof(float));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		IndexBuffer ibo(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
		glm::mat4 orthoProj = glm::ortho(0.0f, (float)window.GetWidth(), 0.0f, (float)window.GetHeight(), 0.1f, 2.0f);
		glm::mat4 perspProj = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		glm::mat4 mvp = perspProj * view * model;
		shader.SetMat4("mvp", mvp);

		while (window.IsRunning())
		{
			/*Render*/
			glClear(GL_COLOR_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			window.OnUpdate();
		}
	}
	glfwTerminate();

	return 0;
}