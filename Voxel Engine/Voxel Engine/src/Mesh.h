#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include <iostream>

struct Vertex
{
	glm::vec3 Position, Normal, Color;

	Vertex(
		glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 normal = glm::vec3(0, 0, 0),
		glm::vec3 color = glm::vec3(0, 0, 0))
		: Position(position), Normal(normal), Color(color)
	{
	}

	//Vertex(const Vertex& vertex)
	//	:Position(vertex.Position), Normal(vertex.Normal), Color(vertex.Color)
	//{
	//	//std::cout << "Vertex Copied!" << std::endl;
	//}
};

class Mesh
{
public:
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	VertexBuffer VBO;
	IndexBuffer IBO;
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	void Update(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void Draw();
	void Clear();
private:
	void SetAttribPointers();
};