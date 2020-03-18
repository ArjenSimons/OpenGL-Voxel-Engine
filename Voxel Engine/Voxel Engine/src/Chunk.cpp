#include "Chunk.h"
#include <iostream>

const glm::ivec3 directionOffset[6]{
	glm::ivec3(0,  1,  0),
	glm::ivec3(0, -1,  0),
	glm::ivec3(0,  0,  1),
	glm::ivec3(0,  0, -1),
	glm::ivec3(1,  0,  0),
	glm::ivec3(-1,  0,  0)
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
	glm::vec3(-1, -1,  1),
	glm::vec3(1, -1,  1),
	glm::vec3(-1,  1,  1),
	glm::vec3(1,  1,  1),
	glm::vec3(-1, -1, -1),
	glm::vec3(1, -1, -1),
	glm::vec3(-1,  1, -1),
	glm::vec3(1,  1, -1)
};

const glm::ivec4 quads[6] =
{
	glm::ivec4(3, 2, 7, 6),    //Up
	glm::ivec4(5, 4, 1, 0),    //Down
	glm::ivec4(1, 0, 3, 2),    //North
	glm::ivec4(4, 5, 6, 7),    //South
	glm::ivec4(5, 1, 7, 3),    //East
	glm::ivec4(0, 4, 2, 6)     //West
};

Block currentBlockType;

Chunk::Chunk()
	:mesh(vertices, indices)
{
	vertices.clear();
	Vertex vertex;
	vertex.Position = glm::vec3(-1.0f, -1.0f, 0.0f);
	vertex.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
	vertex.Color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(vertex);

	Vertex vertex1;
	vertex1.Position = glm::vec3(1.0f, -1.0f, 0.0f);
	vertex1.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
	vertex1.Color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(vertex1);

	Vertex vertex2;
	vertex2.Position = glm::vec3(0.0f, 1.0f, 0.0f);
	vertex2.Normal = glm::vec3(0.0f, 0.0f, 1.0f);
	vertex2.Color = glm::vec3(0.0f, 0.0f, 1.0f);
	vertices.push_back(vertex2);

	indices.clear();
	unsigned int i[3]{
			0, 2, 1
	};
	indices.insert(indices.end(), i, i + 3);

	mesh.Update(vertices, indices);

	InitVoxelData();
	GenerateMesh();
}

Chunk::~Chunk()
{
}


unsigned char Chunk::GetCell(int x, int y, int z) const
{
	return chunk[x][y][z];
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
		if (GetNeighbor(position.x, position.y, position.z, static_cast<Direction>(i)) == 0)
			MakeFace(i, position);
	}
	//MakeFace(3, position);
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

	//std::cout << nVertices << nVertices + 2 << nVertices + 1 << nVertices + 2 << nVertices + 3 << nVertices + 1 << std::endl;
}

void Chunk::GetFaceVertices(int dir, glm::vec3 position)
{
	glm::vec3 normal = normals[dir];
	glm::vec3 color = glm::vec3(0, 0, 1);//GetColor(static_cast<Block>(GetCell(position.x, position.y, position.z)));

	Vertex vertex1(
		normalizedVertices[quads[dir].x] + position,
		normal,
		color
	);
	Vertex vertex2(
		normalizedVertices[quads[dir].y] + position,
		normal,
		color
	);
	Vertex vertex3(
		normalizedVertices[quads[dir].z] + position,
		normal,
		color
	);
	Vertex vertex4(
		normalizedVertices[quads[dir].w] + position,
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
				if (y > z)
					chunk[x][y][z] = AIR;
				else
					chunk[x][y][z] = GRASS;
			}
		}
	}
}