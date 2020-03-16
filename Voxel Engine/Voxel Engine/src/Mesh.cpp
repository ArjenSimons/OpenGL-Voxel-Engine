#include "GL/glew.h"
#include "Mesh.h"
#include <glm/glm.hpp>
#include "Shader.h"

#include <iostream>


Mesh::Mesh(const std::vector<Vertex>& vertices , const std::vector<unsigned int>& indices)
	: m_Vertices(vertices),
	  m_Indices(indices),
	  VBO(&vertices[0], 12 * sizeof(float)),
	  IBO(&indices[0], 3)
{

	ConstructMesh();
}

Mesh::~Mesh()
{
}

void Mesh::ConstructMesh()
{
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, color));
}

void Mesh::Draw() const
{
	//std::cout << "drawing mesh with size: " <<  m_Indices.size() << std::endl;
	//std::cout << m_Indices.size() << std::endl;
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

}

void Mesh::Clear()
{
}