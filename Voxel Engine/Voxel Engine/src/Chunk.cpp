#include "Chunk.h"
#include <iostream>
#include "glm/gtc/noise.hpp"

const glm::ivec3 directionOffset[6]{
	glm::ivec3( 0,  1,  0),	//Up
	glm::ivec3( 0, -1,  0),	//Down
	glm::ivec3( 0,  0,  1),	//South
	glm::ivec3( 0,  0, -1),	//North
	glm::ivec3( 1,  0,  0),	//East
	glm::ivec3(-1,  0,  0)	//West
};

const glm::vec3 normals[6]{
	glm::vec3( 0,  1,  0),
	glm::vec3( 0, -1,  0),
	glm::vec3( 0,  0,  1),
	glm::vec3( 0,  0, -1),
	glm::vec3( 1,  0,  0),
	glm::vec3(-1,  0,  0)
};

const glm::vec3 normalizedVertices[8] =
{
	glm::vec3(-0.5f, -0.5f,  0.5f),
	glm::vec3( 0.5f, -0.5f,  0.5f),
	glm::vec3(-0.5f,  0.5f,  0.5f),
	glm::vec3( 0.5f,  0.5f,  0.5f),
	glm::vec3(-0.5f, -0.5f, -0.5f),
	glm::vec3( 0.5f, -0.5f, -0.5f),
	glm::vec3(-0.5f,  0.5f, -0.5f),
	glm::vec3( 0.5f,  0.5f, -0.5f)
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

Block currentBlockType;

Chunk::Chunk(glm::vec2 offset)
	:mesh(vertices, indices), m_Offset(glm::vec3(offset.x * xSize, 0, offset.y * zSize))
{
	mesh.Update(vertices, indices);

	InitVoxelData();
	GenerateMesh();

	//std::cout << indices.size() << std::endl;
	//std::cout << vertices.size() << std::endl;
	//std::cout << (int)GetCell(0, 0, 0) << std::endl;

	std::cout << m_Offset.x << " " << m_Offset.z << std::endl;
}

Chunk::~Chunk()
{
	//delete[] chunk;
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
	for (unsigned int x = 0; x < xSize; x++)
	{
		for (unsigned int z = 0; z < zSize; z++)
		{
			for (unsigned int y = 0; y < ySize; y++)
			{
				currentBlockType = static_cast<Block>(GetCell(x, y, z));

				if (currentBlockType == AIR)
					continue;

				MakeCube(glm::ivec3(x, y, z));
			}
		}
	}

	mesh.Update(vertices, indices);
}

void Chunk::MakeCube(glm::ivec3 position)
{
	for (int i = 0; i < 6; i++)
	{
		if (GetNeighbor(position.x, position.y, position.z, static_cast<Direction>(i)) == AIR)
			MakeFace(i, position);
	}
}

void Chunk::MakeFace(int dir, glm::vec3 position)
{
	int nVertices = vertices.size();
	//Vertex* faceVertices = GetFaceVertices(dir, position);
	//vertices.insert(vertices.end(), faceVertices, faceVertices + 4);
	GetFaceVertices(dir, position);
	indices.push_back(nVertices);
	indices.push_back(nVertices + 2);
	indices.push_back(nVertices + 1);
	indices.push_back(nVertices + 2);
	indices.push_back(nVertices + 3);
	indices.push_back(nVertices + 1);
}

void Chunk::GetFaceVertices(int dir, glm::vec3 position)
{
	glm::vec3 normal = normals[dir];
	glm::vec3 color = GetColor(static_cast<Block>(GetCell(position.x, position.y, position.z)));

	Vertex vertex1(
		normalizedVertices[quads[dir].x] + position + m_Offset,
		normal,							 
		color							 
	);									 
	Vertex vertex2(						 
		normalizedVertices[quads[dir].y] + position + m_Offset,
		normal,							 
		color							 
	);									 
	Vertex vertex3(						 
		normalizedVertices[quads[dir].z] + position + m_Offset,
		normal,							 
		color							 
	);									 
	Vertex vertex4(						 
		normalizedVertices[quads[dir].w] + position + m_Offset,
		normal,							 
		color
		);

	vertices.push_back(vertex1);
	vertices.push_back(vertex2);
	vertices.push_back(vertex3);
	vertices.push_back(vertex4);

	/*std::cout << faceVetices[0].Position.x << " " << faceVetices[0].Position.y << " " << faceVetices[0].Position.z << std::endl;
	std::cout << faceVetices[1].Position.x << " " << faceVetices[1].Position.y << " " << faceVetices[1].Position.z << std::endl;
	std::cout << faceVetices[2].Position.x << " " << faceVetices[2].Position.y << " " << faceVetices[2].Position.z << std::endl;
	std::cout << faceVetices[3].Position.x << " " << faceVetices[3].Position.y << " " << faceVetices[3].Position.z << std::endl;*/


//	return faceVetices;
}

glm::vec3 Chunk::GetColor(Block block) const
{
	switch (block)
	{
	case (GRASS):
		return glm::vec3(0, 0, 1);
		break;
	default:
		return glm::vec3(0, 0, 1);
	}
}

void Chunk::InitVoxelData()
{
	for (unsigned int x = 0; x < xSize; x++)
	{
		for (unsigned int z = 0; z < zSize; z++)
		{
			for (unsigned int y = 0; y < ySize; y++)
			{
				float height = (ySize - amplitude) +  glm::perlin(glm::vec2(m_Offset.x + x / (float)frequency, m_Offset.z + z / (float)frequency)) * amplitude;
				if (y > height)
				{
					chunk[x][y][z] = AIR;
					//*(chunk + x * ySize * zSize + y * zSize + z) = AIR;
				}
				else
				{
					chunk[x][y][z] = GRASS;

					//*(chunk + x * ySize * zSize + y * zSize + z) = GRASS;
				}
			}
		}
	}
}