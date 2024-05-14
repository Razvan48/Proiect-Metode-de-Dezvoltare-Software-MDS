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
	void drawAliveEntities();
	void drawDeadEntities();

private:
	std::vector<std::shared_ptr<Entity>> entities;

public:
	static Game& get();

	void run();

	void addEntity(std::shared_ptr<Entity> const entity);

	inline std::vector<std::shared_ptr<Entity>>& getEntities() { return this->entities; }
};

