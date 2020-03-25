#include "ChunksManager.h"
#include <iostream>
#include <iterator>

ChunksManager::ChunksManager()
{
	chunksVisibleInViewDist = maxViewDist / chunkSize;
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
	playerChunkCoord.y = playerPos.z / chunkSize;

	for (int zOffset = -chunksVisibleInViewDist; zOffset <= chunksVisibleInViewDist; zOffset++)
	{
		for (int xOffset = -chunksVisibleInViewDist; xOffset <= chunksVisibleInViewDist; xOffset++)
		{
			glm::ivec2 chunkCoord = glm::ivec2(xOffset + playerChunkCoord.x, zOffset + playerChunkCoord.y);
			if (chunks.count(chunkCoord) == 1)
			{
			}
			else
			{
				visibleChunks.push_back(chunkCoord);
				chunks.insert(std::pair<glm::ivec2, Chunk*>(chunkCoord, new Chunk(chunkCoord)));
			}
		}
	}

	//std::list<glm::ivec2>::iterator it;
	//for (it = visibleChunks.begin(); it != visibleChunks.end(); ++it)
	//{
	//	if (it->x > chunksVisibleInViewDist || it->x < -chunksVisibleInViewDist
	//		|| it->y > chunksVisibleInViewDist || it->x < -chunksVisibleInViewDist)
	//	{
	//		void* chunk = &chunks.find(*it);
	//		delete chunk;

	//		chunks.erase(*it);
	//		visibleChunks.remove(*it);
	//	}
	//}


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
