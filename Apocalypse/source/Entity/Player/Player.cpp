#include "Player.h"

#include "../Wall/Wall.h"

#include "../../Constants/Constants.h"

#include "../../ResourceManager/ResourceManager.h"

#include <memory>

Player::Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D, double health = 100.0, double stamina = 100.0, double armor = 0.0) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D),
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, health, stamina, armor)
{

}

Player& Player::get()
{
	// TODO: de schimbat
	static Player instance(4.0, 4.0, 1.0, 1.0, 0.0, 0.5, 0.5, 0.5, {"playerRunning"});

	return instance;
}

void Player::onCollide(CollidableEntity & other, glm::vec2 overlap)
{
	// TODO: nu e totul implementat

	if (dynamic_cast<Wall*>(&other) != nullptr)
	{
		if (overlap.x < overlap.y)
		{
			if (this->x < other.getX())
				this->x -= (overlap.x + Constants::EPS);
			else
				this->x += (overlap.x + Constants::EPS);
		}
		else
		{
			if (this->y < other.getY())
				this->y -= (overlap.y + Constants::EPS);
			else
				this->y += (overlap.y + Constants::EPS);
		}
	}
	/*
	else if (dynamic_cast<Door*>(&other) != nullptr)
	{
		// TODO: implementare
	}
	*/
	else if (dynamic_cast<CollidableEntity*>(&other) != nullptr)
	{
		if (overlap.x < overlap.y)
		{
			if (this->x < other.getX())
			{
				this->x -= (overlap.x + Constants::EPS) / 2.0;
				other.setX(other.getX() + (overlap.x + Constants::EPS) / 2.0);
			}
			else
			{
				this->x += (overlap.x + Constants::EPS) / 2.0;
				other.setX(other.getX() - (overlap.x + Constants::EPS) / 2.0);
			}
		}
		else
		{
			if (this->y < other.getY())
			{
				this->y -= (overlap.y + Constants::EPS) / 2.0;
				other.setY(other.getY() + (overlap.y + Constants::EPS) / 2.0);
			}
			else
			{
				this->y += (overlap.y + Constants::EPS) / 2.0;
				other.setY(other.getY() - (overlap.y + Constants::EPS) / 2.0);
			}
		}
	}
}

Player::~Player()
{

}

