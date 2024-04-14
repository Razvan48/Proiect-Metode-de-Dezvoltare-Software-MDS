#include "Player.h"

#include "../Wall/Wall.h"

#include "../../ResourceManager/ResourceManager.h"
#include "../../Input/InputHandler.h"
#include "../../GlobalClock/GlobalClock.h"

#include <iostream>
#include <memory>

Player::Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, double health = 100.0, double stamina = 100.0, double armor = 0.0) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D),
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, health, stamina, armor)
{

}

Player& Player::get()
{
	static Player instance(5.0, 5.0, 1.0, 1.0, 0.0, 10.0, 0.4, 0.4, std::map<AnimatedEntity::EntityStatus, std::string>
	{
		   { AnimatedEntity::EntityStatus::IDLE, "playerIdle" },
		   { AnimatedEntity::EntityStatus::WALKING, "playerWalking" },
		   { AnimatedEntity::EntityStatus::RUNNING, "playerRunning" },
		   { AnimatedEntity::EntityStatus::TIRED, "playerTired" }
	});

	return instance;
}

void Player::onCollide(CollidableEntity& other, glm::vec2 overlap)
{
	// TODO: nu e totul implementat

	if (dynamic_cast<Wall*>(&other) != nullptr)
	{
		if (overlap.x < overlap.y)
		{
			if (this->x < other.getX())
				this->x -= (overlap.x + CollidableEntity::EPS);
			else
				this->x += (overlap.x + CollidableEntity::EPS);
		}
		else
		{
			if (this->y < other.getY())
				this->y -= (overlap.y + CollidableEntity::EPS);
			else
				this->y += (overlap.y + CollidableEntity::EPS);
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
				this->x -= (overlap.x + CollidableEntity::EPS) / 2.0;
			else
				this->x += (overlap.x + CollidableEntity::EPS) / 2.0;
		}
		else
		{
			if (this->y < other.getY())
				this->y -= (overlap.y + CollidableEntity::EPS) / 2.0;
			else
				this->y += (overlap.y + CollidableEntity::EPS) / 2.0;
		}
	}
}

void Player::update()
{
	// TODO: implementare
}

Player::~Player()
{

}

void Player::setupPlayerInputComponent()
{
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Pressed, std::bind(&Player::moveUp, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Repeat, std::bind(&Player::moveUp, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Pressed, std::bind(&Player::moveDown, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Repeat, std::bind(&Player::moveDown, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Pressed, std::bind(&Player::moveRight, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Repeat, std::bind(&Player::moveRight, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Pressed, std::bind(&Player::moveLeft, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Repeat, std::bind(&Player::moveLeft, this));
}

void Player::moveUp()
{
	this->x = this->x + this->speed * std::cos(this->rotateAngle) * GlobalClock::get().getDeltaTime();
	this->y = this->y + this->speed * std::sin(this->rotateAngle) * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveDown()
{
	this->x = this->x - this->speed * std::cos(this->rotateAngle) * GlobalClock::get().getDeltaTime();
	this->y = this->y - this->speed * std::sin(this->rotateAngle) * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveRight()
{
	this->x = this->x + this->speed * std::sin(this->rotateAngle) * GlobalClock::get().getDeltaTime();
	this->y = this->y - this->speed * std::cos(this->rotateAngle) * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveLeft()
{
	this->x = this->x - this->speed * std::sin(this->rotateAngle) * GlobalClock::get().getDeltaTime();
	this->y = this->y + this->speed * std::cos(this->rotateAngle) * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}



