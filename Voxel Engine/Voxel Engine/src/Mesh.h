#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "VertexBuffer.h"
#include "IndexBuffer.h"

struct Vertex
{
	glm::vec3 position, normal, color;
};

class Mesh
{
public:
	//std::vector<Vertex> m_Vertices;
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
private:
	VertexBuffer VBO;
	IndexBuffer IBO;
public:
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>& indices);
	~Mesh();

	void Draw() const;
	void Clear();
private:
	void ConstructMesh();
};