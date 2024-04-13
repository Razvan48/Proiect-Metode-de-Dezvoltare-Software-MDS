#include "CollisionManager.h"

#include <glm/vec2.hpp>

#include "../Entity/CollidableEntity.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::~CollisionManager()
{

}

CollisionManager& CollisionManager::get()
{
	static CollisionManager instance;

	return instance;
}

void CollisionManager::handleCollisions()
{
	// TODO: implementare

	// Player vs. Map
	for (int i = 0; i < Map::get().getStaticObjects().size(); ++i)
	{
		for (int j = 0; j < Map::get().getStaticObjects()[i].size(); ++j)
		{
			if (dynamic_cast<CollidableEntity*>(&Map::get().getStaticObjects()[i][j]))
			{
				glm::vec2 overlap = Player::get().isInCollision((CollidableEntity&)Map::get().getStaticObjects()[i][j]);
			}
		}
	}
}

