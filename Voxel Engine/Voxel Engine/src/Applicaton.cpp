#include <GL/glew.h>
#include "Window.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include "Mesh.h"

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

		//float positions[72 * 2]{
		//	//south
		//	-1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		//	 1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		//	 1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		//	-1.0f,  1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
		//	//north				 
		//	-1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		//	 1.0f, -1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		//	 1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		//	-1.0f,  1.0f, -1.0f, 0.0f, 0.0f, -1.0f,
		//	//west
		//	-1.0f, -1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		//	-1.0f, -1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
		//	-1.0f,  1.0f,  1.0f, -1.0f, 0.0f, 0.0f,
		//	-1.0f,  1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
		//	//east
		//	 1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		//	 1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
		//	 1.0f,  1.0f,  1.0f, 1.0f, 0.0f, 0.0f,
		//	 1.0f,  1.0f, -1.0f, 1.0f, 0.0f, 0.0f,
		//	//up
		//	-1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		//	 1.0f,  1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		//	 1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		//	-1.0f,  1.0f,  1.0f, 0.0f, 1.0f, 0.0f,
		//	//down
		//	-1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
		//	 1.0f, -1.0f, -1.0f, 0.0f, -1.0f, 0.0f,
		//	 1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,
		//	-1.0f, -1.0f,  1.0f, 0.0f, -1.0f, 0.0f,
		//};

		//unsigned int indices[36]{
		//	0, 1, 2,
		//	0, 2, 3,

		//	4, 5, 6,
		//	4, 6, 7,

		//	8,  9, 10,
		//	8, 10, 11, 

		//	12, 13, 14,
		//	12, 14, 15,

		//	16, 17, 18,
		//	16, 18, 19,

		//	20, 21, 22,
		//	20, 22, 23
		//};

		//VertexBuffer vbo(positions, 72 * 2 * sizeof(float));

		/*glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));*/
		//IndexBuffer ibo(indices, 36);

		float pos[12]{
			-1.0f, -1.0f, 0.0f,
			1.0f, -1.0f, 0.0f,
			0.0f, 1.0f, 0.0f
		};
		//unsigned int ind[3]{
		//	0, 1, 2
		//};

		//VertexBuffer vbo(pos, 12 * sizeof(float));
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		//IndexBuffer ibo(ind, 3);
		std::vector<float> positions(pos, pos + 12);

		std::vector<Vertex> vertices;

		{
			Vertex vertex;
			vertex.position = glm::vec3(-1.0f, -1.0f, 0.0f);
			vertex.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			vertex.color = glm::vec3(0.0f, 0.0f, 1.0f);
			vertices.push_back(vertex);

			Vertex vertex1;
			vertex1.position = glm::vec3(1.0f, -1.0f, 0.0f);
			vertex1.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			vertex1.color = glm::vec3(0.0f, 0.0f, 1.0f);
			vertices.push_back(vertex1);

			Vertex vertex2;
			vertex2.position = glm::vec3(0.0f, 1.0f, 0.0f);
			vertex2.normal = glm::vec3(0.0f, 0.0f, 1.0f);
			vertex2.color = glm::vec3(0.0f, 0.0f, 1.0f);
			vertices.push_back(vertex2);
		}

		unsigned int i[3]{
			0, 1, 2
		};
		std::vector<unsigned int> indices;
		indices.insert(indices.end(), i, i + 3);

		Mesh chunk(positions, indices);

		Shader shader("res/shaders/Basic.shader");

		shader.SetVec3("lightDir", glm::vec3(-0.5f, -0.5f, -0.5f));

		Camera cam(
			glm::vec3(0, 0, 5),
			glm::vec3(0, 0, -1),
			glm::vec3(0, 1, 0)
		);

		glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)window.GetWidth() / (float)window.GetHeight(), 0.1f, 100.0f);
		glm::mat4 model = glm::mat4(1.0f);// glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
		glm::mat4 mvp = projection * cam.GetViewMatrix() * model;

		//glEnable(GL_DEPTH_TEST);
		glfwSwapInterval(0); //Disable vsync

		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		while (window.IsRunning())
		{
			//rotate cube
			//model = glm::rotate(model, glm::radians(-0.1f), glm::vec3(1, 0.5f, 1));
			shader.Bind();
			glm::mat4 mvp = projection * cam.GetViewMatrix() * model;
			shader.SetMat4("mvp", mvp);
			shader.SetMat4("model", model);

			/*Render*/
			glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
			glClearColor(0.5f, 0.5f, 0.5f, 1);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
			chunk.Draw();
			//glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);
			window.OnUpdate();
			cam.ProcessInput(window.GetWindow());
		}
	}
	glfwTerminate();

	return 0;
}