#include "Player.h"

#include <iostream> // TODO: debug
#include <fstream>
#include <memory>
#include <cmath>

#include <nlohmann/json.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "../../WindowManager/WindowManager.h"
#include "../../ResourceManager/ResourceManager.h"
#include "../../Input/InputHandler.h"
#include "../../GlobalClock/GlobalClock.h"
#include "../../Camera/Camera.h"
#include "../../Renderer/SpriteRenderer.h"
#include "../../SoundManager/SoundManager.h"
#include "../../PauseMenu/PauseMenu.h"
#include "../../Game/Game.h"
#include "../Bullet/Bullet.h"
#include "../Wall/Wall.h"

Player::Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, std::vector<EntityStatus> statuses, double runningSpeed, double health = 100.0, double stamina = 100.0, double armor = 0.0) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D, statuses),
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, statuses, health),
	runningSpeed(runningSpeed), stamina(stamina), armor(armor), armorCap(100.0), staminaChangeSpeed(50.0), staminaCap(100.0), gold(0), goldCap(9999999), // TODO: mai frumos pt goldCap se poate?
	moveUpUsed(false), moveDownUsed(false), moveRightUsed(false), moveLeftUsed(false), runUsed(false), interactUsed(false),
	walkingOffsetSize(0.01), runningOffsetSize(0.05),
	walkingOffsetSpeed(10.0), runningOffsetSpeed(15.0)
	// , weapons({nullptr, nullptr, nullptr, nullptr, nullptr}) TODO: !!!!
{

}

Player& Player::get()
{
	static Player instance(5.0, 5.0, 1.0, 1.0, 0.0, 5.0, 0.4, 0.4, std::map<AnimatedEntity::EntityStatus, std::string>
	{
		   { EntityStatus::ARMS_HOLDING_GRENADE, "armsHoldingGrenade" },
		   { EntityStatus::ARMS_HOLDING_KNIFE, "armsHoldingKnife" },
		   { EntityStatus::ARMS_HOLDING_PISTOL, "armsHoldingPistol" },
		   { EntityStatus::ARMS_MOVING_AHEAD, "armsMovingAhead" },
		   { EntityStatus::ARMS_MOVING_AROUND_WALKING, "armsMovingAroundWalking"},
		   { EntityStatus::ARMS_MOVING_AROUND_RUNNING, "armsMovingAroundRunning"},
		   { EntityStatus::ARMS_NOT, "armsNot"},
		   { EntityStatus::ARMS_RELOADING_PISTOL, "armsReloadingPistol"},
		   { EntityStatus::ARMS_USING_GRENADE, "armsUsingGrenade"},
		   { EntityStatus::ARMS_USING_KNIFE, "armsUsingKnife"},
		   { EntityStatus::ARMS_USING_PISTOL, "armsUsingPistol"},
		   { EntityStatus::BODY_IDLE, "bodyIdle"},
		   { EntityStatus::HEAD_ANGRY, "headAngry"},
		   { EntityStatus::HEAD_IDLE, "headIdle"},
		   { EntityStatus::HEAD_SATISFIED, "headSatisfied"},
		   { EntityStatus::HEAD_TIRED, "headTired"},
		   { EntityStatus::LEGS_MOVING_AROUND, "legsMovingAround"},
		   { EntityStatus::LEGS_NOT, "legsNot"}
	},
		{
			EntityStatus::LEGS_NOT,
			EntityStatus::ARMS_MOVING_AHEAD,
			EntityStatus::BODY_IDLE,
			EntityStatus::HEAD_IDLE
		}
	, 7.5);

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
	// head
	if (this->statuses[3] == EntityStatus::HEAD_TIRED)
	{
		this->stamina += this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
		this->stamina = std::min(this->stamina, this->staminaCap);

		if (this->stamina == this->staminaCap)
			this->statuses[3] = EntityStatus::HEAD_IDLE;
	}

	if (this->statuses[3] == EntityStatus::HEAD_TIRED)
	{
		this->statuses[0] = EntityStatus::LEGS_NOT;
		this->statuses[1] = EntityStatus::ARMS_NOT;
		this->statuses[2] = EntityStatus::BODY_IDLE;

		return;
	}

	// body (nu avem nimic, o singura animatie de un frame, atat)

	// arms
	if (this->moveUpUsed == true || this->moveDownUsed == true
		|| this->moveRightUsed == true || this->moveLeftUsed == true)
	{
		if (this->runUsed == false)
		{
			this->statuses[0] = EntityStatus::LEGS_NOT;
			this->statuses[1] = EntityStatus::ARMS_MOVING_AROUND_WALKING;
			this->statuses[2] = EntityStatus::BODY_IDLE;
		}
		else
		{
			this->statuses[0] = EntityStatus::LEGS_MOVING_AROUND;
			this->statuses[1] = EntityStatus::ARMS_MOVING_AROUND_RUNNING;
			this->statuses[2] = EntityStatus::BODY_IDLE;

			this->stamina -= this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
			this->stamina = std::max(0.0, this->stamina);

			if (this->stamina == 0.0)
			{
				this->statuses[3] = EntityStatus::HEAD_TIRED;
			}
		}
	}
	else // IDLE
	{
		this->statuses[0] = EntityStatus::LEGS_NOT;
		this->statuses[1] = EntityStatus::ARMS_MOVING_AHEAD;
		this->statuses[2] = EntityStatus::BODY_IDLE;

		this->stamina += this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
		this->stamina = std::min(this->stamina, this->staminaCap);
	}

	// Sound
	switch (this->statuses[1])
	{
	case EntityStatus::ARMS_MOVING_AHEAD:
		SoundManager::get().pause("walking");
		SoundManager::get().pause("running");
		break;

	case EntityStatus::ARMS_MOVING_AROUND_WALKING:
		SoundManager::get().resume("walking");
		SoundManager::get().pause("running");
		break;

	case EntityStatus::ARMS_MOVING_AROUND_RUNNING:
		SoundManager::get().pause("walking");
		SoundManager::get().resume("running");
		break;
	}

	switch (this->statuses[3])
	{
	case EntityStatus::HEAD_TIRED:
		SoundManager::get().pause("walking");
		SoundManager::get().pause("running");
		break;

	//case EntityStatus::DYING:
	//	SoundManager::get().pause("walking");
	//	SoundManager::get().pause("running");
	//	break;

	default:
		SoundManager::get().pause("walking");
		SoundManager::get().pause("running");
		break;
	}

	if (this->statuses[3] == EntityStatus::HEAD_TIRED)
	{
		return;
	}

	double currentSpeed = this->speed;

	if (this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_RUNNING)
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

	InputHandler::getPlayerInputComponent().bindAction("SHOOT", InputEvent::IE_Pressed, std::bind(&Player::shoot, this));

	InputHandler::getPlayerInputComponent().bindAxis(std::bind(&Player::look, this, std::placeholders::_1, std::placeholders::_2));

	InputHandler::getPlayerInputComponent().bindAction("PAUSE", InputEvent::IE_Pressed, std::bind(&Player::pauseGame, this));

	InputHandler::getPlayerInputComponent().bindAction("INTERACT", InputEvent::IE_Pressed, std::bind(&Player::interact, this));
	InputHandler::getPlayerInputComponent().bindAction("INTERACT", InputEvent::IE_Repeat, std::bind(&Player::interact, this));
	InputHandler::getPlayerInputComponent().bindAction("INTERACT", InputEvent::IE_Released, std::bind(&Player::interactReleased, this));
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

void Player::interact()
{
	this->interactUsed = true;
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

void Player::interactReleased()
{
	this->interactUsed = false;
}

void Player::shoot()
{
	std::cout << "SHOOT" << std::endl;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(Camera::get().screenPosition(this->x, this->y), 0.0f));
	model = glm::rotate(model, glm::radians(static_cast<float>(this->rotateAngle)), glm::vec3(0.0f, 0.0f, 1.0f));

	glm::vec4 bulletRelativeLocation = model * glm::vec4(0.4f, 0.4f, 0.0f, 0.0f);	// TODO: change offset.x and offset.y
	glm::vec2 bulletLocation = glm::vec2(
		this->x + bulletRelativeLocation.x,
		this->y + bulletRelativeLocation.y
	);

	Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, this->rotateAngle, 10.0, 0.3, 0.3, "bullet0", 20.0)); // TODO: change speed
}

void Player::look(double xpos, double ypos)
{
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

void Player::pauseGame()
{
	PauseMenu::get().setIsInGame(false);
	PauseMenu::get().setupPauseMenuInputComponent();
	InputHandler::setInputComponent(InputHandler::getMenuInputComponent());
}

void Player::draw()
{
	/* TODO: exceptii?
	if (this->animationsName2D.find(this->status) == this->animationsName2D.end())
	{
		// exceptii
	}
	*/

	if (this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_WALKING)
	{
		for (int i = 0; i < this->statuses.size(); ++i)
			SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->statuses[i]]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth + this->walkingOffsetSize * glm::sin(this->walkingOffsetSpeed * (GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i])), this->drawHeight + this->walkingOffsetSize * glm::sin(this->walkingOffsetSpeed * (GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]))), this->rotateAngle);
	}
	else if (this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_RUNNING)
	{
		for (int i = 0; i < this->statuses.size(); ++i)
			SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->statuses[i]]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth + this->runningOffsetSize * glm::sin(this->runningOffsetSpeed * (GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i])), this->drawHeight + this->runningOffsetSize * glm::sin(this->runningOffsetSpeed * (GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]))), this->rotateAngle);
	}
	else
	{
		for (int i = 0; i < this->statuses.size(); ++i)
			SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->statuses[i]]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth, this->drawHeight), this->rotateAngle);
	}
}

void Player::save()
{
	std::ofstream saveFile("config/save.json");
	nlohmann::json saveJSON;

	saveJSON["health"] = health;
	saveJSON["healthCap"] = healthCap;

	saveJSON["armor"] = armor;
	saveJSON["armorCap"] = armorCap;

	saveJSON["staminaCap"] = staminaCap;

	saveJSON["gold"] = gold;

	// TODO

	saveFile << std::setw(4) << saveJSON << std::endl;
	saveFile.close();
}

void Player::load()
{
	std::ifstream saveFile("config/save.json");
	nlohmann::json saveJSON;
	saveFile >> saveJSON;
	saveFile.close();

	health = saveJSON["health"].get<double>();
	healthCap = saveJSON["healthCap"].get<double>();

	armor = saveJSON["armor"].get<double>();
	armorCap = saveJSON["armorCap"].get<double>();

	staminaCap = saveJSON["staminaCap"].get<double>();

	gold = saveJSON["gold"].get<int>();

	// TODO
}

