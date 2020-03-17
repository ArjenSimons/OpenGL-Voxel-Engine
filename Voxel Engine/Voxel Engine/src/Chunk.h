#pragma once
#include "glm/glm.hpp"
#include "mesh.h"
#include <vector>;

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
private:
	static const unsigned int xSize = 10;
	static const unsigned int ySize = 10;
	static const unsigned int zSize = 10;
	unsigned char chunk[xSize][ySize][zSize];

	std::vector<Vertex> vertices{ vert };
	std::vector<unsigned int> indices{ 1 };
public:
	Chunk();
	~Chunk();
	Mesh mesh;

	unsigned char GetCell(int x, int y, int z) const;
	unsigned char GetNeighbor(int x, int y, int z, Direction dir) const;
private:
	bool CellIsInMap(glm::ivec3 position) const;
	void GenerateMesh();
	void MakeCube(glm::ivec3 position);
	void MakeFace(int dir, glm::vec3 position);
	Vertex* GetFaceVertices(int dir, glm::vec3 position) const;
	glm::vec3 GetColor(Block block) const;
	void InitVoxelData();
};

