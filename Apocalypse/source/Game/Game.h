#pragma once

#include <vector>
#include <memory>

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

	void updateEntities();
	void drawEntities();

private:
	std::vector<std::shared_ptr<Entity>> entities; // Alte entitati decat cele ce au de a face cu harta / player-ul (deci in mare parte npc-uri, butoane)

public:
	static Game& get();

	void run();

	void addEntity(const std::shared_ptr<Entity>& entity);
};

