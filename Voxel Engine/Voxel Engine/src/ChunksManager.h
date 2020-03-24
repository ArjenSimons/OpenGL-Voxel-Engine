#pragma once
#include <glm/glm.hpp>
#include <unordered_map>
#include <map>
#include "Chunk.h"

struct KeyFuncs
{
	size_t operator()(const glm::vec2& k)const
	{
		return std::hash<int>()(k.x) ^ std::hash<int>()(k.y);
	}

	bool operator()(const glm::vec2& a, const glm::vec2& b)const
	{
		return a.x == b.x && a.y == b.y;
	}
};

typedef std::unordered_map<glm::vec2, Chunk, KeyFuncs, KeyFuncs> MyMap;

class ChunksManager
{
private:
	const unsigned int maxViewDist = 80;
	int chunksVisibleInViewDist;

	MyMap chunks;
	glm::vec2 playerChunkCoord;

	unsigned int chunkSize = Chunk::xSize;
public:
	ChunksManager();
	~ChunksManager();

	void Update(glm::vec3 playerPos);
private:
	void RenderChunks();
};