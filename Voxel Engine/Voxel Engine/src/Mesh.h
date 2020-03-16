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
	float (&m_Positions)[12];
	unsigned int (&m_Indices)[3];
private:
	VertexBuffer VBO;
	IndexBuffer IBO;
public:
	Mesh(float (&positions)[12], unsigned int (&indices)[3]);
	~Mesh();

	void Draw() const;
	void Clear();
private:
	void ConstructMesh();
};