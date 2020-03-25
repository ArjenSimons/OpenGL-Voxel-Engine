#include "ChunksManager.h"
#include <iostream>

ChunksManager::ChunksManager()
	:chunk(new Chunk(glm::vec2(0, 0)))
{
	chunksVisibleInViewDist = maxViewDist / chunkSize;
	
	chunks.insert(std::pair<glm::vec2, Chunk*>(glm::vec2(0, 0),  chunk));
}

ChunksManager::~ChunksManager()
{
	//MyMap::iterator itr;
	//for (itr = chunks.begin(); itr != chunks.end(); ++itr)
	//{
	//	chunks.erase(itr->first);
	//	delete &itr->second;
	//}
}

void ChunksManager::Update(glm::vec3 playerPos)
{
	playerChunkCoord.x = playerPos.x / chunkSize;
	playerChunkCoord.y = playerPos.y / chunkSize;

	for (int zOffset = -chunksVisibleInViewDist; zOffset <= chunksVisibleInViewDist; zOffset++)
	{
		for (int xOffset = -chunksVisibleInViewDist; xOffset <= chunksVisibleInViewDist; xOffset)
		{
			glm::ivec2 chunkCoord = glm::ivec2(xOffset + playerChunkCoord.x, zOffset + playerChunkCoord.y);
			if (chunks.count(chunkCoord) == 1)
			{
			}
			else
			{
				chunks.insert(std::pair<glm::ivec2, Chunk*>(chunkCoord, new Chunk(chunkCoord)));
			}
		}
	}
	RenderChunks();
}

void ChunksManager::RenderChunks()
{
	MyMap::iterator itr;
	for (itr = chunks.begin(); itr != chunks.end(); ++itr)
	{
		itr->second->mesh.Draw();
	}
}
