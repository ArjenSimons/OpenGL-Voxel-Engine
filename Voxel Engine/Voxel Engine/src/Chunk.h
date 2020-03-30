#pragma once
#include "glm/glm.hpp"
#include "mesh.h"
#include <vector>
#include <future>

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
	static const unsigned int xSize = 64;
	static const unsigned int ySize = 64;
	static const unsigned int zSize = 64;
private:
	glm::vec3 m_Offset;

	static const unsigned int amplitude = 10;
	static const unsigned int frequency = 20;
	unsigned char chunk[xSize][ySize][zSize];

	std::vector<Vertex> vertices{ vert };
	std::vector<unsigned int> indices{ 1 };
	
	std::vector<std::future<void>> m_Futures;
	bool dataRetreived = false;
public:
	Chunk(glm::vec2 offset);
	~Chunk();
	Mesh mesh;

	void Update();
	unsigned char GetCell(int x, int y, int z) const;
	unsigned char GetNeighbor(int x, int y, int z, Direction dir) const;
private:
	bool CellIsInMap(glm::ivec3 position) const;
	void RequestMeshData();
	void MeshDataThread();
	void OnMeshDataReceived();
	void GenerateMesh();
	void MakeCube(glm::vec3 &position);
	void MakeFace(int &dir, glm::vec3 &position);
	void GetFaceVertices(int &dir, glm::vec3 &position);
	glm::vec3 GetColor(Block block) const;
	void InitVoxelData();
};