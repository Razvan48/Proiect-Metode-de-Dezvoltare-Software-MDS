#pragma once

#include "../Human/Human.h"

#include <glm/vec2.hpp>

class Player : public virtual Human // singleton
{
protected:

	Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D, double health, double stamina, double armor);
	virtual ~Player();

	Player(const Player& other) = delete;
	Player& operator= (const Player& other) = delete;
	Player(const Player&& other) = delete;
	Player& operator= (const Player&& other) = delete;

public:

	static Player& get();

	//void draw() override; animatedEntity are deja asta implementata
	void onCollide(CollidableEntity& other, glm::vec2 overlap) override;
};