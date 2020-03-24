#include "ChunksManager.h"
#include <iostream>

ChunksManager::ChunksManager()
{
	chunksVisibleInViewDist = maxViewDist / chunkSize;
}

ChunksManager::~ChunksManager()
{
	MyMap::iterator itr;
	for (itr = chunks.begin(); itr != chunks.end(); ++itr)
	{
		delete &itr->second;
	}
}

void ChunksManager::Update(glm::vec3 playerPos)
{
	playerChunkCoord.x = playerPos.x / chunkSize;
	playerChunkCoord.y = playerPos.y / chunkSize;

	for (int yOffset = -chunksVisibleInViewDist; yOffset <= chunksVisibleInViewDist; yOffset++)
	{
		for (int xOffset = -chunksVisibleInViewDist; xOffset <= chunksVisibleInViewDist; xOffset++)
		{
			glm::vec2 chunkCoord = glm::vec2(xOffset + playerPos.x, yOffset + playerPos.y);

			if (chunks.count(chunkCoord) == 1)
			{
			}
			else
			{
				//Chunk* chunk = &Chunk(chunkCoord);
				Chunk* chunk = new Chunk(chunkCoord);
				chunks.insert(std::pair<glm::vec2, Chunk>(chunkCoord, *chunk));
			}
		}
	}
	//std::cout << chunks.size() << std::endl;
	RenderChunks();
}

void ChunksManager::RenderChunks()
{
	MyMap::iterator itr;
	for (itr = chunks.begin(); itr != chunks.end(); ++itr)
	{
		itr->second.mesh.Draw();
	}
}
