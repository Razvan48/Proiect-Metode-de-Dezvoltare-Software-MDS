#pragma once

#include "../windowManager/windowManager.h"
#include "../globalClock/globalClock.h"
#include "../map/map.h"

class Game
{
private:
	Game();
	~Game();
	Game(const Game& other) = delete;
	Game& operator= (const Game& other) = delete;
	Game(const Game&& other) = delete;
	Game& operator= (const Game&& other) = delete;

private:

public:
	static Game& get();

	void loadAssets();
	void run();
};