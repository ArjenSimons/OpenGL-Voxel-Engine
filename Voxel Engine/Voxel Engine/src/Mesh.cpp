#include "GL/glew.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include "Shader.h"

#include <iostream>


Mesh::Mesh(const std::vector<Vertex>& vertices , const std::vector<unsigned int>& indices)
	: m_Vertices(vertices),
	  m_Indices(indices),
	  VBO(&vertices[0], vertices.size() * sizeof(Vertex)),
	  IBO(&indices[0], indices.size())
{

	SetAttribPointers();
}

Mesh::~Mesh()
{
}

void Mesh::SetAttribPointers()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Color));
}

void Mesh::Update(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices)
{
	m_Vertices = vertices;
	m_Indices = indices;
	VBO.Update(&vertices[0], vertices.size() * sizeof(Vertex));
	IBO.Update(&indices[0], indices.size());
}

void Mesh::Draw() const
{
	if (m_Indices.size() > 1 && m_Vertices.size() > 1)
		glDrawElements(GL_TRIANGLES, m_Indices.size(), GL_UNSIGNED_INT, nullptr);
}

void Mesh::Clear()
{
}