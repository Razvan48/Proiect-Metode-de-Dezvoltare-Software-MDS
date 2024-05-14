#include "CollisionManager.h"

#include <glm/vec2.hpp>

#include "../Entity/CollidableEntity.h"
#include "../Entity/Bullet/Bullet.h"
#include "../Entity/Enemy/Enemy.h"

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
	// TODO: e scris ft hardcodat momentan, refactoring

	// Functia de onCollide SE APELEAZA DIN AMBELE PERSPECTIVE ALE CELOR 2 OBIECTE IMPLICATE

	// Player vs. Map
	for (int i = 0; i < Map::get().getMap().size(); ++i)
	{
		for (int j = 0; j < Map::get().getMap()[i].size(); ++j)
		{
			if (std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]) && std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j])->getCollisionActive())
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

	// TODO: refactor
	// Bullets vs. Map
	for (const std::shared_ptr<Entity>& entity : entities)
	{
		if (std::shared_ptr<Bullet> bullet = std::dynamic_pointer_cast<Bullet>(entity))
		{
			bool deleteEntity = false;
			
			for (int i = 0; i < Map::get().getMap().size() && !deleteEntity; ++i)
			{
				for (int j = 0; j < Map::get().getMap()[i].size() && !deleteEntity; ++j)
				{
					if (std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]) && std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j])->getCollisionActive())
					{
						glm::vec2 overlap = bullet->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]));

						if (overlap.x > 0.0 && overlap.y > 0.0)
						{
							bullet->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]), overlap);
							std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j])->onCollide(*bullet, overlap);
						}
					}
				}
			}
		}
	}


	// Player vs. Entities
	// TODO: momentan doar door si enemy (si bullets??)
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<CollidableEntity>(entities[i]) == nullptr)
			continue;

		if (!std::dynamic_pointer_cast<CollidableEntity>(entities[i])->getCollisionActive())
			continue;

		glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(Player::get());

		if (overlap.x > 0.0 && overlap.y > 0.0)
		{
			Player::get().onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(Player::get(), overlap);
		}
	}

	// Bullets vs. Doors
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<Bullet>(entities[i]) == nullptr)
			continue;

		for (int j = 0; j < entities.size(); ++j)
		{
			if (i == j)
				continue;

			if (std::dynamic_pointer_cast<Door>(entities[j]) == nullptr)
				continue;

			if (!std::dynamic_pointer_cast<CollidableEntity>(entities[j])->getCollisionActive())
				continue;

			glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]));

			if (overlap.x > 0.0 && overlap.y > 0.0)
			{
				std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]), overlap);
				std::dynamic_pointer_cast<CollidableEntity>(entities[j])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			}
		}
	}

	// Bullets vs Enemies
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<Bullet>(entities[i]) == nullptr)
			continue;

		for (int j = 0; j < entities.size(); ++j)
		{
			if (i == j)
				continue;

			if (std::dynamic_pointer_cast<Enemy>(entities[j]) == nullptr)
				continue;

			if (!std::dynamic_pointer_cast<CollidableEntity>(entities[j])->getCollisionActive())
				continue;

			glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]));

			if (overlap.x > 0.0 && overlap.y > 0.0)
			{
				std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]), overlap);
				std::dynamic_pointer_cast<CollidableEntity>(entities[j])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			}
		}
	}

	// Enemies vs Enemies
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<Enemy>(entities[i]) == nullptr)
			continue;

		for (int j = 0; j < entities.size(); ++j)
		{
			if (i == j)
				continue;

			if (std::dynamic_pointer_cast<Enemy>(entities[j]) == nullptr)
				continue;

			glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]));

			if (overlap.x > 0.0 && overlap.y > 0.0)
			{
				std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]), overlap);
				std::dynamic_pointer_cast<CollidableEntity>(entities[j])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			}
		}
	}

	// Doors vs Enemies
	for (int i = 0; i < entities.size(); ++i)
	{
		if (std::dynamic_pointer_cast<Door>(entities[i]) == nullptr)
			continue;

		if (!std::dynamic_pointer_cast<CollidableEntity>(entities[i])->getCollisionActive())
			continue;

		for (int j = 0; j < entities.size(); ++j)
		{
			if (i == j)
				continue;

			if (std::dynamic_pointer_cast<Enemy>(entities[j]) == nullptr)
				continue;

			glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[i])->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]));

			if (overlap.x > 0.0 && overlap.y > 0.0)
			{
				std::dynamic_pointer_cast<CollidableEntity>(entities[i])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[j]), overlap);
				std::dynamic_pointer_cast<CollidableEntity>(entities[j])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[i]), overlap);
			}
		}
	}
	
	// Walls vs Enemies
	for (int i = 0; i < Map::get().getMap().size(); ++i)
	{
		for (int j = 0; j < Map::get().getMap()[i].size(); ++j)
		{
			if (std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]) && std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j])->getCollisionActive())
			{
				for (int k = 0; k < entities.size(); ++k)
				{
					if (std::dynamic_pointer_cast<Enemy>(entities[k]) == nullptr)
						continue;

					glm::vec2 overlap = std::dynamic_pointer_cast<CollidableEntity>(entities[k])->isInCollision(*std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]));

					if (overlap.x > 0.0 && overlap.y > 0.0)
					{
						std::dynamic_pointer_cast<CollidableEntity>(entities[k])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j]), overlap);
						std::dynamic_pointer_cast<CollidableEntity>(Map::get().getMap()[i][j])->onCollide(*std::dynamic_pointer_cast<CollidableEntity>(entities[k]), overlap);
					}
				}
			}
		}
	}
}

