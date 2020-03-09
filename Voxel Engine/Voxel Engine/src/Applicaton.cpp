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

		float positions[8]{
			100.0f, 100.0f,
			200.0f, 100.0f,
			200.0f, 200.0f,
			100.0f, 200.0f
		};

		unsigned int indices[6]{
			0, 1, 2,
			0, 2, 3
		};

		VertexBuffer vbo(positions, 8 * sizeof(float));

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);

		IndexBuffer ibo(indices, 6);

		Shader shader("res/shaders/Basic.shader");

		glm::mat4 orthoProj = glm::ortho(0.0f, (float)window.GetWidth(), 0.0f, (float)window.GetHeight(), 0.0f, 1.0f);
		shader.SetMat4("mvp", orthoProj);

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