#include "Player.h"

#include "../Wall/Wall.h"

#include "../../ResourceManager/ResourceManager.h"
#include "../../Input/InputHandler.h"
#include "../../GlobalClock/GlobalClock.h"
#include "../../WindowManager/WindowManager.h"
#include "../../Camera/Camera.h"

#include <iostream> // Debug
#include <memory>
#include <cmath>

Player::Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, double runningSpeed, double health = 100.0, double stamina = 100.0, double armor = 0.0) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D),
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, health),
	runningSpeed(runningSpeed), stamina(stamina), armor(armor), armorCap(100.0), staminaChangeSpeed(50.0), staminaCap(100.0),
	moveUpUsed(false), moveDownUsed(false), moveRightUsed(false), moveLeftUsed(false), runUsed(false)
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
	}, 7.5);

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
	if (this->getStatus() == EntityStatus::TIRED)
	{
		this->stamina += this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
		this->stamina = std::min(this->stamina, this->staminaCap);

		if (this->stamina == this->staminaCap)
			this->updateStatus(EntityStatus::IDLE);

		return;
	}

	if (this->moveUpUsed == true || this->moveDownUsed == true
		|| this->moveRightUsed == true || this->moveLeftUsed == true)
	{
		if (this->runUsed == false)
		{
			this->updateStatus(EntityStatus::WALKING);
		}
		else
		{
			this->updateStatus(EntityStatus::RUNNING);

			this->stamina -= this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
			this->stamina = std::max(0.0, this->stamina);

			if (this->stamina == 0.0)
			{
				this->updateStatus(EntityStatus::TIRED);

				return;
			}
		}
	}
	else // IDLE
	{
		this->updateStatus(EntityStatus::IDLE);

		this->stamina += this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
		this->stamina = std::min(this->stamina, this->staminaCap);
	}

	double currentSpeed = this->speed;

	if (this->getStatus() == EntityStatus::RUNNING)
		currentSpeed = this->runningSpeed;

	double xOffset = 0.0;
	double yOffset = 0.0;

	if (this->moveRightUsed)
		xOffset += currentSpeed * GlobalClock::get().getDeltaTime();
	if (this->moveLeftUsed)
		xOffset -= currentSpeed * GlobalClock::get().getDeltaTime();
	if (this->moveUpUsed)
		yOffset += currentSpeed * GlobalClock::get().getDeltaTime();
	if (this->moveDownUsed)
		yOffset -= currentSpeed * GlobalClock::get().getDeltaTime();

	if (xOffset != 0.0 && yOffset != 0.0)
	{
		xOffset /= glm::sqrt(2.0);
		yOffset /= glm::sqrt(2.0);
	}

	this->x += xOffset;
	this->y += yOffset;
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

	InputHandler::getPlayerInputComponent().bindAction("RUN", InputEvent::IE_Pressed, std::bind(&Player::run, this));
	InputHandler::getPlayerInputComponent().bindAction("RUN", InputEvent::IE_Repeat, std::bind(&Player::run, this));
	InputHandler::getPlayerInputComponent().bindAction("RUN", InputEvent::IE_Released, std::bind(&Player::runReleased, this));

	InputHandler::getPlayerInputComponent().bindAxis(std::bind(&Player::look, this, std::placeholders::_1, std::placeholders::_2));
}

void Player::moveUp()
{
	this->moveUpUsed = true;
}

void Player::moveDown()
{
	this->moveDownUsed = true;
}

void Player::moveRight()
{
	this->moveRightUsed = true;
}

void Player::moveLeft()
{
	this->moveLeftUsed = true;
}

void Player::run()
{
	this->runUsed = true;
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

void Player::runReleased()
{
	this->runUsed = false;
}

void Player::look(double xpos, double ypos)
{
	// double xCenter = static_cast<double>(WindowManager::get().getWindowWidth()) / 2.0;
	// double yCenter = static_cast<double>(WindowManager::get().getWindowHeight()) / 2.0;

	// Asa mi se pare mai bine.
	glm::vec2 posCenter = Camera::get().screenPosition(this->x, this->y) + glm::vec2(WindowManager::get().getWindowWidth() / 2.0, WindowManager::get().getWindowHeight() / 2.0);
	double xCenter = posCenter.x;
	double yCenter = posCenter.y;

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

