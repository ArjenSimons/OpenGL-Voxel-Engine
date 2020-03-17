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
	static const int xSize = 10;
	static const int ySize = 10;
	static const int zSize = 10;
	unsigned char chunk[xSize][ySize][zSize];

	std::vector<Vertex> vertices{ vert };
	std::vector<unsigned int> indices{ 1 };
public:
	Chunk();
	~Chunk();
	Mesh mesh;

	unsigned char GetCell(int x, int y, int z);
	unsigned char GetNeighbor(int x, int y, int z, Direction dir);
private:
	bool CellIsInMap(glm::ivec3 position);
};

