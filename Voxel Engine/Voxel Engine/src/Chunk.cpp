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

const glm::vec2 UVGrassTop[4] = {
	glm::vec2(0.5f, 0.5f),
	glm::vec2(1.0f, 0.5f),
	glm::vec2(0.5f, 1.0f),
	glm::vec2(1.0f, 1.0f)
};

const glm::vec2 UVGrassSide[4] = {
	glm::vec2(0.0f, 0.5f),
	glm::vec2(0.5f, 0.5f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(0.5f, 1.0f)
};

const glm::vec2 UVDirt[4] = {
	glm::vec2(0.0f, 0.0f),
	glm::vec2(0.5f, 0.0f),
	glm::vec2(0.0f, 1.0f),
	glm::vec2(0.5f, 1.0f)
};

const glm::vec2 UVStone[4] = {
	glm::vec2(0.5f, 0.0f),
	glm::vec2(1.0f, 0.0f),
	glm::vec2(0.5f, 0.5f),
	glm::vec2(1.0f, 0.5f)
};

Chunk::Chunk(glm::vec2 offset)
	:mesh(vertices, indices), m_Offset(glm::vec3(offset.x * xSize, 0, offset.y * zSize))
{
	//std::cout << "startCopy?" << std::endl;

	//mesh.Update(vertices, indices);

	//float startTime = glfwGetTime();

	RequestMeshData();
	//InitVoxelData();
	//std::cout << "afterInit" << std::endl;

	//float midTime = glfwGetTime();
	//float initTime = midTime - startTime;

	//GenerateMesh();
	//OnMeshDataReceived();

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
}


void Chunk::Update()
{
	if (dataRetreived)
	{
		OnMeshDataReceived();
		dataRetreived = false;
	}
	else
	{
		mesh.Draw();
	}
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

	float height = 0;
	height = (ySize - amplitude) + glm::perlin(glm::vec2((m_Offset.x + neighborPos.x) / (float)frequency, (m_Offset.z + neighborPos.z) / (float)frequency)) * amplitude;

	if (y > height || (y <= 0 && dir == DOWN))
		return 0;

	return 1;
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
static std::mutex mutex;
void Chunk::RequestMeshData()
{
	m_Futures.push_back(std::async(std::launch::async, [this] { this->MeshDataThread(); }));
}


void Chunk::MeshDataThread()
{
	std::lock_guard<std::mutex> lock(mutex);
	InitVoxelData();
	GenerateMesh();

	dataRetreived = true;
}

void Chunk::OnMeshDataReceived()
{
	float startTime = glfwGetTime();

	mesh.Update(vertices, indices);

	float endTime = glfwGetTime();
	std::cout << "updateMeshTime " << endTime - startTime << std::endl;
}

void Chunk::GenerateMesh()
{
	vertices.clear();
	indices.clear();
	//std::cout << "inside generate mesh" << std::endl;
	vertices.reserve(27000);
	indices.reserve(37000);
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


	//float endTime = glfwGetTime();
	//std::cout << "updateMeshTime " << endTime - midTime << std::endl;

}

void Chunk::MakeCube(glm::vec3 &position)
{
	for (int i = 0; i < 6; i++)
	{
		//if (static_cast<Direction>(i) != AIR && static_cast<Direction>(i) != GRASS)
		//	std::cout << static_cast<Direction>(i) << std::endl;
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

	Block blockType = static_cast<Block>(GetCell(position.x, position.y, position.z));
	glm::vec3 color = GetColor(blockType);
	const glm::vec2* uvCoords = GetUVs(blockType, dir);

	vertices.emplace_back(
		normalizedVertices[quads[dir].x] + position + m_Offset,
		normals[dir],
		color,
		uvCoords[0]);
	vertices.emplace_back(
		normalizedVertices[quads[dir].y] + position + m_Offset,
		normals[dir],
		color,
		uvCoords[1]);
	vertices.emplace_back(
		normalizedVertices[quads[dir].z] + position + m_Offset,
		normals[dir],
		color,
		uvCoords[2]);
	vertices.emplace_back(
		normalizedVertices[quads[dir].w] + position + m_Offset,
		normals[dir],
		color,
		uvCoords[3]);
}

glm::vec3 Chunk::GetColor(Block block) const
{
	switch (block)
	{
	case (GRASS):
		return glm::vec3(0.9f, 0.8f, 0.5f);
		break;
	default:
		return glm::vec3(0, 0, 1);
	}
}

const glm::vec2* Chunk::GetUVs(Block block, int & dir) const
{
	switch (block)
	{
	case(GRASS):
		if (dir == UP)
		{
			return &UVGrassTop[0];
		}
		else return &UVGrassSide[0];
		break;
	case(DIRT):
		return &UVDirt[0];
		break;
	case(STONE):
		return &UVStone[0];
		break;
	}
	return nullptr;
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
				if (y < ySize - amplitude)
					chunk[x][y][z] = STONE;
				else
					chunk[x][y][z] = GRASS;
			}
		}
	}
}