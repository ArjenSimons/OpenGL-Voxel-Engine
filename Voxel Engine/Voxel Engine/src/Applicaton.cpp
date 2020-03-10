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

		float positions[72]{
			//south
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			//north
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			//west
			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,
			//east
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			//up
			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			//down
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

		};

		unsigned int indices[36]{
			0, 1, 2,
			0, 2, 3,

			4, 5, 6,
			4, 6, 7,

			8,  9, 10,
			8, 10, 11, 

			12, 13, 14,
			12, 14, 15,

			16, 17, 18,
			16, 18, 19,

			20, 21, 22,
			20, 22, 23
		};

		VertexBuffer vbo(positions, 72 * sizeof(float));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

		IndexBuffer ibo(indices, 36);

		Shader shader("res/shaders/Basic.shader");
		
		glm::mat4 view = glm::lookAt(
			glm::vec3(0, 0, 5),
			glm::vec3(0, 0, 0),
			glm::vec3(0, 1.0f, 0)
		);
		glm::mat4 orthoProj = glm::ortho(0.0f, (float)window.GetWidth(), 0.0f, (float)window.GetHeight(), 0.1f, 2.0f);
		glm::mat4 perspProj = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
		glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

		while (window.IsRunning())
		{
			/*Render*/
			glClear(GL_COLOR_BUFFER_BIT);
			model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(0.7f, 0.2, 0));

			glm::mat4 mvp = perspProj * view * model;
			shader.SetMat4("mvp", mvp);

			glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			window.OnUpdate();
		}
	}
	glfwTerminate();

	return 0;
}