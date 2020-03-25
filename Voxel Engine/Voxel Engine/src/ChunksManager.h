#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <map>
#include <list>
#include "Chunk.h"
#include "Shader.h"

struct KeyFuncs
{
	size_t operator()(const glm::ivec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::ivec2& a, const glm::ivec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

typedef std::unordered_map<glm::ivec2, Chunk*, KeyFuncs, KeyFuncs> MyMap;

class ChunksManager
{
private:
	const unsigned int maxViewDist = 80;
	int chunksVisibleInViewDist;
	unsigned int chunkSize = Chunk::xSize;

	MyMap chunks;
	glm::ivec2 playerChunkCoord;
	Chunk* chunk;

public:
	ChunksManager();
	~ChunksManager();

	void Update(glm::vec3 playerPos);
private:
	void RenderChunks();
};