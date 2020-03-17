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
private:
	std::vector<Vertex> m_Vertices;
	std::vector<unsigned int> m_Indices;
	VertexBuffer VBO;
	IndexBuffer IBO;
public:
	Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	~Mesh();

	void Update(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices);
	void Draw() const;
	void Clear();
private:
	void ConstructMesh();
};