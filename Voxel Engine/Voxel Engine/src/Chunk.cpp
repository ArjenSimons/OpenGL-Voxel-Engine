#include "Chunk.h"
#include <iostream>
#include "glm/gtc/noise.hpp"
#include <GLFW/glfw3.h>

const glm::ivec3 directionOffset[6]{
	glm::ivec3(0,  1,  0),	//Up
	glm::ivec3(0, -1,  0),	//Down
	glm::ivec3(0,  0,  1),	//South
	glm::ivec3(0,  0, -1),	//North
	glm::ivec3(1,  0,  0),	//East
	glm::ivec3(-1,  0,  0)	//West
};

const glm::vec3 normals[6]{
	glm::vec3(0,  1,  0),
	glm::vec3(0, -1,  0),
	glm::vec3(0,  0,  1),
	glm::vec3(0,  0, -1),
	glm::vec3(1,  0,  0),
	glm::vec3(-1,  0,  0)
};

const glm::vec3 normalizedVertices[8] =
{
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3(0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3(0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3(0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3(0.5f,  0.5f, -0.5f)
};

const glm::ivec4 quads[6] =
{
	glm::ivec4(3, 2, 7, 6),	//Up
	glm::ivec4(5, 4, 1, 0),	//Down
	glm::ivec4(1, 0, 3, 2),	//South
	glm::ivec4(4, 5, 6, 7),	//North
	glm::ivec4(5, 1, 7, 3),	//East
	glm::ivec4(0, 4, 2, 6)	//West
};

Chunk::Chunk(glm::vec2 offset)
	:mesh(vertices, indices), m_Offset(glm::vec3(offset.x * xSize, 0, offset.y * zSize))
{
	//std::cout << "startCopy?" << std::endl;

	//mesh.Update(vertices, indices);

	//float startTime = glfwGetTime();

	InitVoxelData();
	//std::cout << "afterInit" << std::endl;

	//float midTime = glfwGetTime();
	//float initTime = midTime - startTime;

	GenerateMesh();
	//float endTime = glfwGetTime();

	//float meshTime = endTime - midTime;

	//float totalTime = endTime - startTime;

	//std::cout << "InitTime: " << initTime << std::endl;
	//std::cout << "MeshTime: " << meshTime << std::endl;
	//std::cout << "TotalTime: " << totalTime << std::endl;
	//std::cout << "vertices size: " << vertices.size() << std::endl;
	//std::cout << "indices size: " << indices.size() << std::endl;

	//std::cout << indices.size() << std::endl;
	//std::cout << vertices.size() << std::endl;
	//std::cout << (int)GetCell(0, 0, 0) << std::endl;

	//std::cout << m_Offset.x << " " << m_Offset.z << std::endl;
}

Chunk::~Chunk()
{
	//delete &mesh;
}


unsigned char Chunk::GetCell(int x, int y, int z) const
{
	return chunk[x][y][z];//*(chunk + x * ySize * zSize + y * zSize + z);
}

unsigned char Chunk::GetNeighbor(int x, int y, int z, Direction dir) const
{
	glm::ivec3 neighborPos = glm::ivec3(x, y, z) + directionOffset[dir];

	if (CellIsInMap(neighborPos))
		return GetCell(neighborPos.x, neighborPos.y, neighborPos.z);

	return 0;
}

bool Chunk::CellIsInMap(glm::ivec3 position) const
{
	if (position.x < 0 ||
		position.x >= xSize ||
		position.y < 0 ||
		position.y >= ySize ||
		position.z < 0 ||
		position.z >= zSize)
	{
		return false;
	}
	return true;
}

void Chunk::GenerateMesh()
{
	vertices.clear();
	indices.clear();
	//std::cout << "inside generate mesh" << std::endl;
	vertices.reserve(25000);
	indices.reserve(35000);
	//float startTime = glfwGetTime();


	for (unsigned int x = 0; x < xSize; x++)
	{
		for (unsigned int z = 0; z < zSize; z++)
		{
			for (unsigned int y = 0; y < ySize; y++)
			{
				if (static_cast<Block>(GetCell(x, y, z)) == AIR)
					continue;

				glm::vec3 pos = glm::vec3(x, y, z);
				MakeCube(pos);
			}
		}
	}

	//float midTime = glfwGetTime();
	//std::cout << "generateMeshTime " << midTime - startTime << std::endl;


	mesh.Update(vertices, indices);
	//float endTime = glfwGetTime();
	//std::cout << "updateMeshTime " << endTime - midTime << std::endl;

}

void Chunk::MakeCube(glm::vec3 &position)
{
	for (int i = 0; i < 6; i++)
	{
		if (GetNeighbor(position.x, position.y, position.z, static_cast<Direction>(i)) == AIR)
			MakeFace(i, position);
	}
}

void Chunk::MakeFace(int &dir, glm::vec3 &position)
{
	//std::cout << "start inside makeFace" << std::endl;
	int nVertices = vertices.size();
	//Vertex* faceVertices = GetFaceVertices(dir, position);
	//vertices.insert(vertices.end(), faceVertices, faceVertices + 4);

	GetFaceVertices(dir, position);
	//std::cout << "mid inside makeFace" << std::endl;
	indices.emplace_back(nVertices);
	indices.emplace_back(nVertices + 2);
	indices.emplace_back(nVertices + 1);
	indices.emplace_back(nVertices + 2);
	indices.emplace_back(nVertices + 3);
	indices.emplace_back(nVertices + 1);
}

void Chunk::GetFaceVertices(int &dir, glm::vec3 &position)
{
	glm::vec3 color = GetColor(static_cast<Block>(GetCell(position.x, position.y, position.z)));
	vertices.emplace_back(
		normalizedVertices[quads[dir].x] + position + m_Offset,
		normals[dir],
		color);
	vertices.emplace_back(
		normalizedVertices[quads[dir].y] + position + m_Offset,
		normals[dir],
		color);
	vertices.emplace_back(
		normalizedVertices[quads[dir].z] + position + m_Offset,
		normals[dir],
		color);
	vertices.emplace_back(
		normalizedVertices[quads[dir].w] + position + m_Offset,
		normals[dir],
		color);
}

glm::vec3 Chunk::GetColor(Block block) const
{
	switch (block)
	{
	case (GRASS):
		return glm::vec3(226, 200, 147);
		break;
	default:
		return glm::vec3(0, 0, 1);
	}
}

void Chunk::InitVoxelData()
{

	float hightOffset = ySize - amplitude;
	for (unsigned int x = 0; x < xSize; x++)
	{
		for (unsigned int z = 0; z < zSize; z++)
		{
			float height = hightOffset + glm::perlin(glm::vec2((m_Offset.x + x) / (float)frequency, (m_Offset.z + z) / (float)frequency)) * amplitude;

			for (unsigned int y = 0; y <= height; y++)
			{
				chunk[x][y][z] = GRASS;
			}
		}
	}
}