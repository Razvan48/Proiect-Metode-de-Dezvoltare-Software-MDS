#include <queue>
#include <memory>

#include <iostream> // TODO: debug

#include "Enemy.h"
#include "../Player/Player.h"
#include "../../Map/Map.h"
#include "../../Game/Game.h"
#include "../Wall/Wall.h"

Enemy::Enemy(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses, double health, double rotateSpeed)
	: Entity(x, y, drawWidth, drawHeight, rotateAngle, speed)
	, CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight)
	, AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D, statuses)
	, Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, statuses, health)
	, AIEntity(x, y, drawWidth, drawHeight, rotateAngle, speed)
	, rotateSpeed(rotateSpeed), probToChangeDir(1.0 / 250.0)
	, currentTarget(std::make_pair(x, y)), nextTarget(std::make_pair(x, y))
{

}


void Enemy::pathFindingTarget()
{
	// Clear
	while (!this->q.empty())
	{
		this->q.pop();
	}
	this->visitedCells.clear();
	//



	this->blockedCell.resize(Map::get().getMap().size());
	this->cellDistance.resize(Map::get().getMap().size());
	for (int i = 0; i < Map::get().getMap().size(); ++i)
	{
		this->blockedCell[i].resize(Map::get().getMap()[i].size());
		this->cellDistance[i].resize(Map::get().getMap()[i].size());
	}
	for (int i = 0; i < Map::get().getMap().size(); ++i)
	{
		for (int j = 0; j < Map::get().getMap()[i].size(); ++j)
		{
			this->blockedCell[i][j] = false;
			this->cellDistance[i][j] = 0;
		}
	}

	for (int i = 0; i < Map::get().getMap().size(); ++i)
	{
		for (int j = 0; j < Map::get().getMap()[i].size(); ++j)
		{
			if (std::dynamic_pointer_cast<Wall>(Map::get().getMap()[i][j]))
			{
				this->blockedCell[i][j] = true;
			}
		}
	}
	for (int i = 0; i < Game::get().getEntities().size(); ++i)
	{
		if (std::dynamic_pointer_cast<Door>(Game::get().getEntities()[i]) && std::dynamic_pointer_cast<Door>(Game::get().getEntities()[i])->getCollisionActive())
		{
			int xDoor = static_cast<int>(Game::get().getEntities()[i]->getX());
			int yDoor = static_cast<int>(Game::get().getEntities()[i]->getY());
			this->blockedCell[yDoor][xDoor] = true;
		}
	}

	int xCell = static_cast<int>(this->x);
	int yCell = static_cast<int>(this->y);
	int xTarget = static_cast<int>(Player::get().getX());
	int yTarget = static_cast<int>(Player::get().getY());

	if (xCell == xTarget && yCell == yTarget)
	{
		this->cellDistance[yTarget][xTarget] = 1;
		this->nextTarget = std::make_pair(xTarget + 0.5, yTarget + 0.5);
		return;
	}

	this->cellDistance[yCell][xCell] = 1;
	this->q.emplace(std::make_pair(xCell, yCell));
	this->visitedCells.emplace_back(std::make_pair(xCell, yCell));

	bool done = false;
	while (!done && !this->q.empty())
	{
		int currentX = this->q.front().first;
		int currentY = this->q.front().second;
		this->q.pop();

		for (int i = 0; i < AIEntity::neighbors.size(); ++i)
		{
			int newX = currentX + AIEntity::neighbors[i].first;
			int newY = currentY + AIEntity::neighbors[i].second;

			if (this->blockedCell[newY][newX] || this->cellDistance[newY][newX] > 0)
				continue;

			this->cellDistance[newY][newX] = this->cellDistance[currentY][currentX] + 1;

			if (newX == xTarget && newY == yTarget)
			{
				done = true;
				break;
			}

			this->q.emplace(std::make_pair(newX, newY));
			this->visitedCells.emplace_back(std::make_pair(newX, newY));
		}
	}

	if (this->cellDistance[yTarget][xTarget] > 0)
	{
		std::pair<int, int> lastCurrentCell = std::make_pair(-1, -1);
		std::pair<int, int> currentCell = std::make_pair(xTarget, yTarget);

		while (currentCell != std::make_pair(xCell, yCell))
		{
			std::vector<std::pair<int, int>> previousCells;

			for (int i = 0; i < AIEntity::neighbors.size(); ++i)
			{
				int newX = currentCell.first + AIEntity::neighbors[i].first;
				int newY = currentCell.second + AIEntity::neighbors[i].second;

				if (this->cellDistance[newY][newX] + 1 == this->cellDistance[currentCell.second][currentCell.first])
				{
					previousCells.emplace_back(std::make_pair(newX, newY));
				}
			}

			int previousCellsIndex = (int)(random01() * ((double)previousCells.size() - AIEntity::EPSILON));
			lastCurrentCell = currentCell;
			currentCell = previousCells[previousCellsIndex];
		}

		this->nextTarget = std::make_pair(lastCurrentCell.first + 0.5, lastCurrentCell.second + 0.5);
	}
	else
	{
		int indexRandom = (int)(random01() * ((double)this->visitedCells.size() - AIEntity::EPSILON));
		this->nextTarget = std::make_pair(this->visitedCells[indexRandom].first + 0.5, this->visitedCells[indexRandom].second + 0.5);
	}
}

void Enemy::onTargetReach()
{
	// TODO: (sau putem lasa asa)
}

bool Enemy::nearTarget()
{
	if (this->cellDistance[(int)Player::get().getY()][(int)Player::get().getX()] == 0)
		return false;
	return this->cellDistance[(int)Player::get().getY()][(int)Player::get().getX()] - 1 < (int)this->nearTargetRadius;
}

void Enemy::update()
{
	this->pathFindingTarget();

	if (this->nearTarget())
	{
		this->statuses[0] = EntityStatus::LEGS_NOT;

		this->onTargetReach();

		return;
	}

	this->statuses[0] = EntityStatus::LEGS_MOVING_AROUND;

	if ((this->x - this->currentTarget.first) * (this->x - this->currentTarget.first) +
		(this->y - this->currentTarget.second) * (this->y - this->currentTarget.second) < AIEntity::EPSILON_MOVEMENT * AIEntity::EPSILON_MOVEMENT)
	{
		this->currentTarget = this->nextTarget;
	}
	else
	{
		double currentTargetAngle = std::atan2f(this->currentTarget.second - this->y, this->currentTarget.first - this->x);
		this->x += this->speed * std::cos(currentTargetAngle) * GlobalClock::get().getDeltaTime();
		this->y += this->speed * std::sin(currentTargetAngle) * GlobalClock::get().getDeltaTime();
	}

	double currentTargetAngle = glm::degrees(std::atan2f(this->currentTarget.second - this->y, this->currentTarget.first - this->x));
	if (currentTargetAngle < 0.0)
		currentTargetAngle += 360.0;

	double angleDist = std::min(std::abs(this->rotateAngle - currentTargetAngle),
		std::abs(360.0 - std::max(this->rotateAngle, currentTargetAngle) +
			std::min(this->rotateAngle, currentTargetAngle)));

	// this->rotateAngle = currentTargetAngle;

	if (angleDist > AIEntity::EPSILON_ANGLE)
	{
		if (std::abs(this->rotateAngle - currentTargetAngle) <
			std::abs(360.0 - std::max(this->rotateAngle, currentTargetAngle) +
				std::min(this->rotateAngle, currentTargetAngle)))
		{
			if (this->rotateAngle < currentTargetAngle) // sens trigonometric
			{
				this->rotateAngle += this->rotateSpeed * GlobalClock::get().getDeltaTime();
				while (this->rotateAngle >= 360.0)
					this->rotateAngle -= 360.0;
			}
			else // sens opus
			{
				this->rotateAngle -= this->rotateSpeed * GlobalClock::get().getDeltaTime();
				while (this->rotateAngle < 0.0)
					this->rotateAngle += 360.0;
			}
		}
		else // sens trigonometric
		{
			this->rotateAngle += this->rotateSpeed * GlobalClock::get().getDeltaTime();
			while (this->rotateAngle >= 360.0)
				this->rotateAngle -= 360.0;
		}
	}
}

Enemy::~Enemy()
{

}