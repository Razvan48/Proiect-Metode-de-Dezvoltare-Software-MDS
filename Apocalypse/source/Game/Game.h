#pragma once

#include <vector>

#include "../Entity/Entity.h"

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
	void loadResources();

private:

	std::vector<Entity> entities; // Alte entitati decat cele ce au de a face cu harta / player-ul (deci in mare parte npc-uri, butoane)

public:
	static Game& get();

	void run();
};

