#pragma once

#include <vector>
#include <memory>

#include "../Entity/Entity.h"
#include "../Entity/DeadBody/DeadBody.h"

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
	void drawDeadBodies();
	void drawEntities();

private:
	std::vector<std::shared_ptr<DeadBody>> deadBodies;
	std::vector<std::shared_ptr<Entity>> entities;

	const int MAX_NUM_DEAD_BODIES;

public:
	static Game& get();

	void run();

	void addEntity(std::shared_ptr<Entity> const entity);
	void addDeadBody(std::shared_ptr<DeadBody> const deadBody);

	inline std::vector<std::shared_ptr<Entity>>& getEntities() { return this->entities; }
	inline std::vector<std::shared_ptr<DeadBody>>& getDeadBodies() { return this->deadBodies; }

	inline void clear() { deadBodies.clear(); entities.clear(); };
};

