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
	, rotateSpeed(rotateSpeed), lastChosenCell(std::make_pair(-1, -1)), chosenCell(std::make_pair(-1, -1)), chosenCellIndex(-1), probToChangeDir(1.0 / 250.0)
{

}


void Enemy::pathFindingTarget()
{
	// clear
	while (!this->q.empty())
	{
		this->q.pop();
	}
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
		if (std::dynamic_pointer_cast<Door>(Game::get().getEntities()[i]))
		{
			int xDoor = static_cast<int>(Game::get().getEntities()[i]->getX() + 0.5);
			int yDoor = static_cast<int>(Game::get().getEntities()[i]->getY() + 0.5);
			this->blockedCell[yDoor][xDoor] = true;
		}
	}

	int xCell = static_cast<int>(this->x + 0.5);
	int yCell = static_cast<int>(this->y + 0.5);
	int xTarget = static_cast<int>(Player::get().getX() + 0.5);
	int yTarget = static_cast<int>(Player::get().getY() + 0.5);

	this->cellDistance[yCell][xCell] = 1;
	this->q.emplace(std::make_pair(xCell, yCell));

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
		}
	}

	if (this->cellDistance[yTarget][xTarget] > 0)
	{
		std::pair<int, int> lastCurrentCell = std::make_pair(-1, -1);
		std::pair<int, int> currentCell = std::make_pair(xTarget, yTarget);

		while (currentCell != std::make_pair(xCell, yCell))
		{
			for (int i = 0; i < AIEntity::neighbors.size(); ++i)
			{
				int newX = currentCell.first + AIEntity::neighbors[i].first;
				int newY = currentCell.second + AIEntity::neighbors[i].second;

				if (this->cellDistance[newY][newX] + 1 == this->cellDistance[currentCell.second][currentCell.first])
				{
					lastCurrentCell = currentCell;
					currentCell = std::make_pair(newX, newY);
					break;
				}
			}
		}

		std::cout << "DIST: " << this->cellDistance[lastCurrentCell.second][lastCurrentCell.first] << ' ' << lastCurrentCell.second << ' ' << lastCurrentCell.first << '\n';

		this->lastChosenCell = this->chosenCell;
		this->chosenCell = std::make_pair(lastCurrentCell.first - xCell, lastCurrentCell.second - yCell);
	}
	else
	{
		if (this->lastChosenCell != std::make_pair(-1, -1))
		{
			this->chosenCell = this->lastChosenCell;

			if (AIEntity::random01() < this->probToChangeDir)
			{
				this->chosenCell = AIEntity::neighbors[(int)(AIEntity::random01() * ((int)AIEntity::neighbors.size() - AIEntity::EPSILON))];
				this->lastChosenCell = this->chosenCell;
			}
		}
		else
		{
			this->chosenCell = AIEntity::neighbors[(int)(AIEntity::random01() * ((int)AIEntity::neighbors.size() - AIEntity::EPSILON))];
			this->lastChosenCell = this->chosenCell;
		}
	}

	for (int i = 0; i < AIEntity::neighbors.size(); ++i)
	{
		if (this->chosenCell == AIEntity::neighbors[i])
		{
			this->chosenCellIndex = i;
			break;
		}
	}

	//debug
	std::cout << xCell << ' ' << yCell << ' ' << xTarget << ' ' << yTarget << ' ' <<
		AIEntity::neighbors[this->chosenCellIndex].first << ' ' << AIEntity::neighbors[this->chosenCellIndex].second << std::endl;

	/*
	for (int i = 25; i >= 0; --i)
	{
		for (int j = 0; j <= 25; ++j)
		{
			std::cout << this->blockedCell[i][j] << ' ';
		}
		std::cout << '\n';
	}
	*/
}

void Enemy::onTargetReach()
{
	std::cout << "NEAR!\n";
	// TODO: (sau putem lasa asa)
}

bool Enemy::nearTarget()
{
	return (this->x - Player::get().getX()) * (this->x - Player::get().getX()) +
		(this->y - Player::get().getY()) * (this->y - Player::get().getY()) < this->nearTargetRadius * this->nearTargetRadius;
}

void Enemy::update()
{
	if (this->nearTarget())
	{
		this->onTargetReach();
		return;
	}

	this->pathFindingTarget();




	/*
	for (int i = 25; i >= 0; --i)
	{
		for (int j = 0; j <= 25; ++j)
		{
			std::cout << this->cellDistance[i][j] << ' ';
		}
		std::cout << std::endl;
	}
	std::cout << "DIRECTIE " << this->chosenCell.first << ' ' << this->chosenCell.second << '\n';
	std::cout << "########################\n";
	*/





	int xCell = static_cast<int>(this->x + 0.5);
	int yCell = static_cast<int>(this->y + 0.5);
	int newX = xCell + AIEntity::neighbors[this->chosenCellIndex].first;
	int newY = yCell + AIEntity::neighbors[this->chosenCellIndex].second;

	int deltaX = AIEntity::neighbors[this->chosenCellIndex].first;
	int deltaY = AIEntity::neighbors[this->chosenCellIndex].second;

	double speedDeltaX = this->speed * std::cos(glm::radians(this->rotateAngle)) * GlobalClock::get().getDeltaTime();
	double speedDeltaY = this->speed * std::sin(glm::radians(this->rotateAngle)) * GlobalClock::get().getDeltaTime();

	//debug
	//this->x = newX;
	//this->y = newY;
	//

	/*
	if (speedDeltaX * deltaX + speedDeltaY * deltaY > 0.0)
	{
		this->x += speedDeltaX;
		this->y += speedDeltaY;
	}
	*/
	//if (speedDeltaX * deltaX > 0.0)
	//	this->x += speedDeltaX;
	//if (speedDeltaY * deltaY > 0.0)
	//	this->y += speedDeltaY;
	this->x += this->speed * AIEntity::neighbors[this->chosenCellIndex].first * GlobalClock::get().getDeltaTime();
	this->y += this->speed * AIEntity::neighbors[this->chosenCellIndex].second * GlobalClock::get().getDeltaTime();

	double anglesDistance = std::min(std::abs(this->rotateAngle - AIEntity::neighborsAngles[this->chosenCellIndex]),
		std::abs(360.0 - std::max(this->rotateAngle, AIEntity::neighborsAngles[this->chosenCellIndex]) +
			std::min(this->rotateAngle, AIEntity::neighborsAngles[this->chosenCellIndex])));

	if (anglesDistance > AIEntity::EPSILON_ANGLE)
	{
		if (std::abs(this->rotateAngle - AIEntity::neighborsAngles[this->chosenCellIndex]) <
			std::abs(360.0 - std::max(this->rotateAngle, AIEntity::neighborsAngles[this->chosenCellIndex]) +
				std::min(this->rotateAngle, AIEntity::neighborsAngles[this->chosenCellIndex]))) // rotatie in sens trigonometric
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
}

Enemy::~Enemy()
{

}