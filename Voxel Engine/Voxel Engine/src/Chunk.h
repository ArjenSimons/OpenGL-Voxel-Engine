#pragma once
#include "glm/glm.hpp"
#include "mesh.h"
#include <vector>

enum Direction
{
	UP,
	DOWN,
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum Block
{
	AIR,
	GRASS,
	DIRT,
	STONE
};

static Vertex vert;

class Chunk
{
public:
	static const unsigned int xSize = 32;
	static const unsigned int ySize = 32;
	static const unsigned int zSize = 32;
private:
	glm::vec3 m_Offset;

	static const unsigned int amplitude = 10;
	static const unsigned int frequency = 20;
	unsigned char* chunk = new unsigned char[xSize * ySize * zSize];

	std::vector<Vertex> vertices{ vert };
	std::vector<unsigned int> indices{ 1 };
public:
	Chunk(glm::vec2 offset);
	~Chunk();
	Mesh mesh;

	unsigned char GetCell(int x, int y, int z) const;
	unsigned char GetNeighbor(int x, int y, int z, Direction dir) const;
private:
	bool CellIsInMap(glm::ivec3 position) const;
	void GenerateMesh();
	void MakeCube(glm::ivec3 position);
	void MakeFace(int dir, glm::vec3 position);
	void GetFaceVertices(int dir, glm::vec3 position);
	glm::vec3 GetColor(Block block) const;
	void InitVoxelData();
	glm::vec3 GetOffset(){ 
		glm::vec3 newOffset = glm::vec3(m_Offset.x * xSize, m_Offset.y * ySize, 0);
		return newOffset; 
	};
};