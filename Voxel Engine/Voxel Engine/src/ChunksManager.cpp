#include "ChunksManager.h"
#include <iostream>
#include <iterator>

ChunksManager::ChunksManager()
{
	chunksVisibleInViewDist = maxViewDist / chunkSize;
}

ChunksManager::~ChunksManager()
{
}

void ChunksManager::Update(glm::vec3 playerPos)
{
	playerChunkCoord.x = playerPos.x / chunkSize;
	playerChunkCoord.y = playerPos.z / chunkSize;

	for (int zOffset = -chunksVisibleInViewDist; zOffset <= chunksVisibleInViewDist; zOffset++)
	{
		for (int xOffset = -chunksVisibleInViewDist; xOffset <= chunksVisibleInViewDist; xOffset++)
		{
			glm::ivec2 chunkCoord = glm::ivec2(xOffset + playerChunkCoord.x, zOffset + playerChunkCoord.y);
			if (chunks.count(chunkCoord) != 1)
			{
				visibleChunks.push_back(chunkCoord);
				chunks.insert(std::pair<glm::ivec2, std::unique_ptr<Chunk>>(chunkCoord, new Chunk(chunkCoord)));
			}
		}
	}

	for (auto it = visibleChunks.begin(); it != visibleChunks.end(); it++)
	{
		if (it->x > playerChunkCoord.x + chunksVisibleInViewDist + 1 || it->x < playerChunkCoord.x - chunksVisibleInViewDist - 1 ||
			it->y > playerChunkCoord.y + chunksVisibleInViewDist + 1 || it->y < playerChunkCoord.y - chunksVisibleInViewDist - 1)
		{
			chunks.erase(*it);

			if (it != visibleChunks.begin())
				visibleChunks.erase(it--);
			else
				visibleChunks.erase(it++);
		}
	}


	RenderChunks(playerChunkCoord);
}

void ChunksManager::RenderChunks(glm::vec2 playerCoord)
{
	MyMap::iterator itr;
	for (itr = chunks.begin(); itr != chunks.end(); ++itr)
	{
		if (itr->first.x <= playerChunkCoord.x + chunksVisibleInViewDist && itr->first.x >= playerChunkCoord.x - chunksVisibleInViewDist
			&& itr->first.y <= playerChunkCoord.y + chunksVisibleInViewDist && itr->first.y >= playerChunkCoord.y - chunksVisibleInViewDist)
		{
			itr->second->mesh.Draw();
		}
	}
}
