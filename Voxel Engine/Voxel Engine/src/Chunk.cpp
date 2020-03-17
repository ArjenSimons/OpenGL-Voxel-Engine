#include "Chunk.h"
#include <iostream>

const glm::ivec3 directionOffset[6]{
	glm::ivec3(0,  1,  0),
	glm::ivec3(0, -1,  0),
	glm::ivec3(0,  0, -1),
	glm::ivec3(0,  0,  1),
	glm::ivec3(1,  0,  0),
	glm::ivec3(-1,  0,  0)
};

Chunk::Chunk()
	:mesh(vertices, indices)
{
	vertices.clear();
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

	indices.clear();
	unsigned int i[3]{
			0, 2, 1
	};
	indices.insert(indices.end(), i, i + 3);

	mesh.Update(vertices, indices);

	InitVoxelData();

}

Chunk::~Chunk()
{
}


unsigned char Chunk::GetCell(int x, int y, int z)
{
	return chunk[x][y][z];
}

unsigned char Chunk::GetNeighbor(int x, int y, int z, Direction dir)
{
	glm::ivec3 neighborPos = glm::ivec3(x, y, z) + directionOffset[dir];

	if (CellIsInMap(neighborPos))
		return GetCell(neighborPos.x, neighborPos.y, neighborPos.z);

	return 0;
}

bool Chunk::CellIsInMap(glm::ivec3 position)
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

void Chunk::InitVoxelData()
{
	for (int x = 0; x < xSize; x++)
	{
		for (int z = 0; z < zSize; z++)
		{
			for (size_t y = 0; y < ySize; y++)
			{
				if (y > z)
					chunk[x][y][z] = AIR;
				else
					chunk[x][y][z] = GRASS;
			}
		}
	}
}


