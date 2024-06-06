#include "WaveManager.h"
#include "../GlobalClock/GlobalClock.h"
#include "../Map/Map.h"
#include "../Entity/Wall/Wall.h"
#include "../Entity/Player/Player.h"
#include "../Game/Game.h"
#include "../Entity/Enemy/Enemy.h"
#include "../Random/Random.h"

WaveManager::WaveManager(const double waveCoolDown, bool inWave, double timeWaveEnded, int numEnemiesPerTurn, int numFinishedWaves) :
	waveCoolDown(waveCoolDown), inWave(inWave), timeWaveEnded(timeWaveEnded), numEnemiesPerTurn(numEnemiesPerTurn), numFinishedWaves(numFinishedWaves)
{

}

WaveManager& WaveManager::get()
{
	static WaveManager instance(10.0, false, GlobalClock::get().getCurrentTime(), 7, 0);
	return instance;
}

WaveManager::~WaveManager()
{

}

void WaveManager::bfsSearch()
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
	for (int i = 0; i < Map::get().getDoors().size(); ++i)
	{
		if (!Map::get().getDoors()[i]->getCollisionActive())
			continue;

		int xDoor = static_cast<int>(Map::get().getDoors()[i]->getX());
		int yDoor = static_cast<int>(Map::get().getDoors()[i]->getY());
		this->blockedCell[yDoor][xDoor] = true;
	}

	int xSource = static_cast<int>(Player::get().getX());
	int ySource = static_cast<int>(Player::get().getY());

	this->cellDistance[ySource][xSource] = 1;
	this->q.emplace(std::make_pair(xSource, ySource));
	this->visitedCells.emplace_back(std::make_pair(xSource, ySource));


	while (!this->q.empty())
	{
		int currentX = this->q.front().first;
		int currentY = this->q.front().second;
		this->q.pop();

		for (int i = 0; i < this->neighbors.size(); ++i)
		{
			int newX = currentX + this->neighbors[i].first;
			int newY = currentY + this->neighbors[i].second;

			if (this->blockedCell[newY][newX] || this->cellDistance[newY][newX] > 0)
				continue;

			this->cellDistance[newY][newX] = this->cellDistance[currentY][currentX] + 1;

			this->q.emplace(std::make_pair(newX, newY));
			this->visitedCells.emplace_back(std::make_pair(newX, newY));
		}
	}
}

void WaveManager::update()
{
	if (this->inWave)
	{
		int numEnemiesActive = 0;
		std::vector<std::shared_ptr<Entity>>& entities = Game::get().getEntities();
		for (int i = 0; i < entities.size(); ++i)
		{
			if (std::dynamic_pointer_cast<Enemy>(entities[i]))
				++numEnemiesActive;
		}

		if (numEnemiesActive == 0)
		{
			this->inWave = false;
			++this->numFinishedWaves;
			this->timeWaveEnded = GlobalClock::get().getCurrentTime();
		}
	}
	else if (GlobalClock::get().getCurrentTime() - this->timeWaveEnded > this->waveCoolDown)
	{
			this->inWave = true;
			bfsSearch();

			//aici spaunez zombii
			for (int i = 0; i < this->numEnemiesPerTurn && !this->visitedCells.empty(); ++i)
			{
				// Varianta Random
				/*
				int indexRandom = (int)(Random::random01() * ((double)this->visitedCells.size() - Random::EPSILON));
				std::pair<int, int> spawnPos = this->visitedCells[indexRandom];
				std::swap(this->visitedCells[indexRandom], this->visitedCells[(int)this->visitedCells.size() - 1]);
				this->visitedCells.pop_back();
				Game::get().addEntity(std::shared_ptr<Enemy>(new Enemy(1.0, 1.0, 1.0, 1.0, 90.0, 5.0, 0.5, 0.5, std::map<AnimatedEntity::EntityStatus, std::string>
				{
					{ AnimatedEntity::EntityStatus::ARMS_STAYING_AHEAD, "enemy0ArmsStayingAhead" },
					{ AnimatedEntity::EntityStatus::ARMS_NOT, "enemy0ArmsNot" },
					{ AnimatedEntity::EntityStatus::BODY_IDLE, "enemy0BodyIdle" },
					{ AnimatedEntity::EntityStatus::HEAD_IDLE, "enemy0HeadIdle" },
					{ AnimatedEntity::EntityStatus::LEGS_MOVING_AROUND, "enemy0LegsMovingAround" },
					{ AnimatedEntity::EntityStatus::LEGS_NOT, "enemy0LegsNot" }
				},
				{
					AnimatedEntity::EntityStatus::LEGS_NOT,
					AnimatedEntity::EntityStatus::ARMS_STAYING_AHEAD,
					AnimatedEntity::EntityStatus::BODY_IDLE,
					AnimatedEntity::EntityStatus::HEAD_IDLE
				}, 100.0, 1000.0, 0.01, 0.75)));
				*/

				// Varianta unde ii punem cat mai departe de player (Problema: ajung sa se spauneze toti cam in acelasi loc si se incurca intre ei)
				/*
				std::pair<int, int> spawnPos = this->visitedCells[(int)this->visitedCells.size() - 1];
				this->visitedCells.pop_back();
				Game::get().addEntity(std::shared_ptr<Enemy>(new Enemy(0.5 + spawnPos.first, 0.5 + spawnPos.second, 1.0, 1.0, 90.0, 5.0, 0.5, 0.5, std::map<AnimatedEntity::EntityStatus, std::string>
				{
					{ AnimatedEntity::EntityStatus::ARMS_STAYING_AHEAD, "enemy0ArmsStayingAhead" },
					{ AnimatedEntity::EntityStatus::ARMS_NOT, "enemy0ArmsNot" },
					{ AnimatedEntity::EntityStatus::BODY_IDLE, "enemy0BodyIdle" },
					{ AnimatedEntity::EntityStatus::HEAD_IDLE, "enemy0HeadIdle" },
					{ AnimatedEntity::EntityStatus::LEGS_MOVING_AROUND, "enemy0LegsMovingAround" },
					{ AnimatedEntity::EntityStatus::LEGS_NOT, "enemy0LegsNot" }
				},
				{
					AnimatedEntity::EntityStatus::LEGS_NOT,
					AnimatedEntity::EntityStatus::ARMS_STAYING_AHEAD,
					AnimatedEntity::EntityStatus::BODY_IDLE,
					AnimatedEntity::EntityStatus::HEAD_IDLE
				}, 100.0, 1000.0, 0.01, 0.75)));
				*/

				// Varianta unde ii punem cat mai departe de player dar facem sarituri de cate k celule (problema, daca nu avem k celule disponibile? va crashui, TODO:)
				int k = 50;
				std::pair<int, int> spawnPos = this->visitedCells[(int)this->visitedCells.size() - k];
				std::swap(this->visitedCells[(int)this->visitedCells.size() - k], this->visitedCells[(int)this->visitedCells.size() - 1]);
				this->visitedCells.pop_back();
				Game::get().addEntity(std::shared_ptr<Enemy>(new Enemy(0.5 + spawnPos.first, 0.5 + spawnPos.second, 1.0, 1.0, 90.0, 5.0, 0.5, 0.5, std::map<AnimatedEntity::EntityStatus, std::string>
				{
					{ AnimatedEntity::EntityStatus::ARMS_STAYING_AHEAD, "enemy0ArmsStayingAhead" },
					{ AnimatedEntity::EntityStatus::ARMS_NOT, "enemy0ArmsNot" },
					{ AnimatedEntity::EntityStatus::BODY_IDLE, "enemy0BodyIdle" },
					{ AnimatedEntity::EntityStatus::HEAD_IDLE, "enemy0HeadIdle" },
					{ AnimatedEntity::EntityStatus::LEGS_MOVING_AROUND, "enemy0LegsMovingAround" },
					{ AnimatedEntity::EntityStatus::LEGS_NOT, "enemy0LegsNot" }
				},
				{
					AnimatedEntity::EntityStatus::LEGS_NOT,
					AnimatedEntity::EntityStatus::ARMS_STAYING_AHEAD,
					AnimatedEntity::EntityStatus::BODY_IDLE,
					AnimatedEntity::EntityStatus::HEAD_IDLE
				}, 100.0, 1000.0, 0.01, 0.75)));
			}
	}
}