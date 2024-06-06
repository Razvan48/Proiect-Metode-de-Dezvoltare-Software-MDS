#pragma once

#include <vector>
#include <queue>

class WaveManager
{
private:

	WaveManager(const double waveCoolDown, bool inWave, double timeWaveEnded, int numEnemiesPerTurn, int numFinishedWaves);
	~WaveManager();
	WaveManager(const WaveManager& other) = delete;
	WaveManager& operator= (const WaveManager& other) = delete;
	WaveManager(const WaveManager&& other) = delete;
	WaveManager& operator= (const WaveManager&& other) = delete;

	const double waveCoolDown;
	bool inWave;
	double timeWaveEnded;
	int numEnemiesPerTurn;
	int numFinishedWaves;

	std::vector<std::vector<bool>> blockedCell;
	std::vector<std::vector<int>> cellDistance;
	std::queue<std::pair<int, int>> q;
	std::vector<std::pair<int, int>> visitedCells;

	void bfsSearch();

	const std::vector<std::pair<int, int>> WaveManager::neighbors = { {0, -1}, {0, 1}, {-1, 0}, {1, 0} };
	const std::vector<std::pair<int, int>> WaveManager::extendedNeighbors = { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };

public:

	static WaveManager& get();

	int getNumFinishedWaves() const { return this->numFinishedWaves; }
	int getCurrentWaveNumber() const { return this->numFinishedWaves + 1; }

	void update(); // TODO:
};