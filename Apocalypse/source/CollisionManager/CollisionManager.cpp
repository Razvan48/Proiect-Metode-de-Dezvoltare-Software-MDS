#include "CollisionManager.h"

#include <glm/vec2.hpp>

#include "../Entity/CollidableEntity.h"

#include <iostream> // TODO: delete
#include <memory>

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

void CollisionManager::handleCollisions(std::vector<std::shared_ptr<Entity>>& entities)
{
	// TODO: implementare

	// Functia de onCollide SE APELEAZA DIN AMBELE PERSPECTIVE ALE CELOR 2 OBIECTE IMPLICATE

	// Player vs. Map
	for (int i = 0; i < Map::get().getMap().size(); ++i)
	{
		for (int j = 0; j < Map::get().getMap()[i].size(); ++j)
		{
			if (std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]))
			{
				glm::vec2 overlap = Player::get().isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]));

				if (overlap.x > 0.0 && overlap.y > 0.0)
				{
					Player::get().onCollide(*std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]), overlap);
					std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j])->onCollide(Player::get(), overlap);
				}
			}
		}
	}

	// Player vs. Entities
	// momentan doar door
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<CollidableEntity>(entities[i]) == nullptr)
			continue;

		glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(Player::get());

		if (overlap.x > 0.0 && overlap.y > 0.0)
		{
			Player::get().onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(Player::get(), overlap);
		}
	}

	// Others
	/*
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<CollidableEntity>(entities[i]) == nullptr)
			continue;

		for (int j = i + 1; j < entities.size(); ++j)
		{
			if (std::dynamic_pointer_cast<CollidableEntity>(entities[j]) == nullptr)
				continue;

			glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]));

			if (overlap.x > 0.0 && overlap.y > 0.0)
			{
				std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]), overlap);
				std::dynamic_pointer_cast<CollidableEntity>(entities[j])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			}
		}
	}
	*/
}

