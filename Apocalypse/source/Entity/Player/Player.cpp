#include "Player.h"

#include "../Wall/Wall.h"

#include "../../ResourceManager/ResourceManager.h"
#include "../../Input/InputHandler.h"
#include "../../GlobalClock/GlobalClock.h"
#include "../../WindowManager/WindowManager.h"

#include <iostream>
#include <memory>
#include <cmath>

Player::Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, double health = 100.0, double stamina = 100.0, double armor = 0.0) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D),
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, health, stamina, armor)
{

}

Player& Player::get()
{
	static Player instance(5.0, 5.0, 1.0, 1.0, 0.0, 5.0, 0.4, 0.4, std::map<AnimatedEntity::EntityStatus, std::string>
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

Player::~Player()
{

}

void Player::update()
{
	if (this->moveUpUsed == false && this->moveDownUsed == false
		&& this->moveRightUsed == false && this->moveLeftUsed == false)
	{
		this->updateStatus(EntityStatus::IDLE);
	}

	/*
	if (this->moveUpUsed == true && this->moveRightUsed != this->moveLeftUsed)
	{
		this->y += this->speed * GlobalClock::get().getDeltaTime() * 1.0 / glm::sqrt(2.0);

		if (this->moveRightUsed == true)
		{
			this->x += this->speed * GlobalClock::get().getDeltaTime() * 1.0 / glm::sqrt(2.0);
		}
		else
		{
			this->x -= this->speed * GlobalClock::get().getDeltaTime() * 1.0 / glm::sqrt(2.0);
		}
	}
	else if (this->moveDownUsed == true && this->moveRightUsed != this->moveLeftUsed)
	{
		this->y -= this->speed * GlobalClock::get().getDeltaTime() * 1.0 / glm::sqrt(2.0);

		if (this->moveRightUsed == true)
		{
			this->x += this->speed * GlobalClock::get().getDeltaTime() * 1.0 / glm::sqrt(2.0);
		}
		else
		{
			this->x -= this->speed * GlobalClock::get().getDeltaTime() * 1.0 / glm::sqrt(2.0);
		}
	}
	else
	{

	}
	*/
}

void Player::setupPlayerInputComponent()
{
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Pressed, std::bind(&Player::moveUp, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Repeat, std::bind(&Player::moveUp, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Released, std::bind(&Player::moveUpReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Pressed, std::bind(&Player::moveDown, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Repeat, std::bind(&Player::moveDown, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Released, std::bind(&Player::moveDownReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Pressed, std::bind(&Player::moveRight, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Repeat, std::bind(&Player::moveRight, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Released, std::bind(&Player::moveRightReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Pressed, std::bind(&Player::moveLeft, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Repeat, std::bind(&Player::moveLeft, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Released, std::bind(&Player::moveLeftReleased, this));

	InputHandler::getPlayerInputComponent().bindAxis(std::bind(&Player::look, this, std::placeholders::_1, std::placeholders::_2));
}

void Player::moveUp()
{
	this->moveUpUsed = true;

	this->y += this->speed * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveDown()
{
	this->moveDownUsed = true;

	this->y -= this->speed * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveRight()
{
	this->moveRightUsed = true;

	this->x += this->speed * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveLeft()
{
	this->moveLeftUsed = true;

	this->x -= this->speed * GlobalClock::get().getDeltaTime();

	this->updateStatus(EntityStatus::WALKING);
}

void Player::moveUpReleased()
{
	this->moveUpUsed = false;
}

void Player::moveDownReleased()
{
	this->moveDownUsed = false;
}

void Player::moveRightReleased()
{
	this->moveRightUsed = false;
}

void Player::moveLeftReleased()
{
	this->moveLeftUsed = false;
}

void Player::look(double xpos, double ypos)
{
	double xCenter = static_cast<double>(WindowManager::get().getWindowWidth()) / 2.0;
	double yCenter = static_cast<double>(WindowManager::get().getWindowHeight()) / 2.0;

	double xLungime = std::abs(xpos - xCenter);
	double yLungime = std::abs(ypos - yCenter);

	// cadran raportat la centru
	if (xpos > xCenter && ypos < yCenter) // cadran I
	{
		this->rotateAngle = glm::degrees(glm::atan(yLungime / xLungime));
	}
	else if (xpos < xCenter && ypos < yCenter) // cadran II
	{
		this->rotateAngle = 90.0 + glm::degrees(glm::atan(xLungime / yLungime));
	}
	else if (xpos < xCenter && ypos > yCenter) // cadran III
	{
		this->rotateAngle = 180.0 + glm::degrees(glm::atan(yLungime / xLungime));
	}
	else if (xpos > xCenter && ypos > yCenter) // cadran IV
	{
		this->rotateAngle = 270.0 + glm::degrees(glm::atan(xLungime / yLungime));
	}
}

