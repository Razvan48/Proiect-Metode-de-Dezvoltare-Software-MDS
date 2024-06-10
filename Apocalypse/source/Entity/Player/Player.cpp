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
#include "../../MenuManager/PauseMenu/PauseMenu.h"
#include "../../Game/Game.h"
#include "../Bullet/Bullet.h"
#include "../Wall/Wall.h"
#include "../Door/Door.h"
#include "../../MenuManager/MenuManager.h"
#include "../../MenuManager/ShopMenu/ShopMenu.h"
#include "../../Random/Random.h"
#include "../Explosion/Explosion.h"

Player::Player(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses, double runningSpeed, double health = 100.0, double stamina = 100.0, double armor = 0.0, int numKills = 0) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D, statuses),
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, statuses, health),
	runningSpeed(runningSpeed), stamina(stamina), armor(armor), armorCap(100.0), staminaChangeSpeed(50.0), staminaCap(100.0), gold(0), goldCap(9999999), // TODO: mai frumos pt goldCap se poate?
	moveUpUsed(false), moveDownUsed(false), moveRightUsed(false), moveLeftUsed(false), runUsed(false), interactUsed(false),
	walkingOffsetSize(0.01), runningOffsetSize(0.05),
	walkingOffsetSpeed(10.0), runningOffsetSpeed(15.0),
	weapons({ std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "fist0", 0.0, 0.0, 0.5, 1, 10.0, Weapon::WeaponType::FIST, 0.75, "", "", "")
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "knife0", 0.0, 0.0, 0.5, 20, 15.0, Weapon::WeaponType::KNIFE, 0.75, "knifeLook", "knifeDraw", "knifeLook") // knife
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "pistol0", 0.0, 0.0, 0.5, 20, 25.0, Weapon::WeaponType::REVOLVER, 0.0, "revolverReload", "revolverDraw", "revolverEmpty") // revolver
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "shotgun0", 0.0, 0.0, 1.0, 4, 50.0, Weapon::WeaponType::SHOTGUN, 0.0, "shotgunReload", "shotgunDraw", "shotgunEmpty") // shotgun
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "automated1", 0.0, 0.0, 0.3, 25, 35.0, Weapon::WeaponType::AK47, 0.0, "ak47Reload", "ak47Draw", "ak47Empty") // ak47
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "automated0", 0.0, 0.0, 0.3, 25, 35.0, Weapon::WeaponType::M4, 0.0, "m4a1Reload", "m4a1Draw", "m4a1Empty") // m4
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "minigun0", 0.0, 0.0, 0.2, 50, 10.0, Weapon::WeaponType::MINIGUN, 0.0, "minigunReload", "minigunDraw", "minigunEmpty") // minigun
		//, nullptr // grenade		TODO: sunete
		, std::make_shared<Weapon>(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, "grenade0", 0.0, 0.0, 1.0, (1<<30), 100.0, Weapon::WeaponType::GRENADE, 0.0, "minigunReload", "minigunDraw", "minigunEmpty") // TODO: schimbat sunete la grenada
		}),
	currentWeaponIndex(0),
	isTired(false), isWalking(false), isRunning(false), isShooting(false), numKills(numKills)
{
	// TODO: test
	bullets[Weapon::WeaponType::REVOLVER] = 1024;
	bullets[Weapon::WeaponType::SHOTGUN] = 1024;
	bullets[Weapon::WeaponType::AK47] = 1024;
	bullets[Weapon::WeaponType::M4] = 1024;
	bullets[Weapon::WeaponType::MINIGUN] = 1024;
	bullets[Weapon::WeaponType::GRENADE] = 1024;
}

Player& Player::get()
{
	static Player instance(10.5, 10.5, 1.0, 1.0, 0.0, 5.0, 0.4, 0.4, std::map<AnimatedEntity::EntityStatus, std::string>
	{
		   { EntityStatus::ARMS_HOLDING_GRENADE, "player0ArmsHoldingGrenade" },
		   { EntityStatus::ARMS_HOLDING_KNIFE, "player0ArmsHoldingKnife" },
		   { EntityStatus::ARMS_HOLDING_PISTOL, "player0ArmsHoldingPistol" },
		   { EntityStatus::ARMS_HOLDING_SHOTGUN, "player0ArmsHoldingShotgun"},
		   { EntityStatus::ARMS_HOLDING_AK47, "player0ArmsHoldingAK47"},
		   { EntityStatus::ARMS_HOLDING_M4, "player0ArmsHoldingM4"},
		   { EntityStatus::ARMS_MOVING_AHEAD, "player0ArmsMovingAhead" },
		   { EntityStatus::ARMS_MOVING_AROUND_WALKING, "player0ArmsMovingAroundWalking"},
		   { EntityStatus::ARMS_MOVING_AROUND_RUNNING, "player0ArmsMovingAroundRunning"},
		   { EntityStatus::ARMS_NOT, "player0ArmsNot"},
		   { EntityStatus::ARMS_RELOADING_PISTOL, "player0ArmsReloadingPistol"},
		   { EntityStatus::ARMS_RELOADING_SHOTGUN, "player0ArmsReloadingShotgun"},
		   { EntityStatus::ARMS_RELOADING_AK47, "player0ArmsReloadingAK47"},
		   { EntityStatus::ARMS_RELOADING_M4, "player0ArmsReloadingM4"},
		   { EntityStatus::ARMS_USING_GRENADE, "player0ArmsUsingGrenade"},
		   { EntityStatus::ARMS_USING_KNIFE, "player0ArmsUsingKnife"},
		   { EntityStatus::ARMS_USING_PISTOL, "player0ArmsUsingPistol"},
		   { EntityStatus::ARMS_USING_SHOTGUN, "player0ArmsUsingShotgun"},
		   { EntityStatus::ARMS_USING_FIST, "player0ArmsUsingFist"},
		   { EntityStatus::ARMS_USING_AK47, "player0ArmsUsingAK47"},
		   { EntityStatus::ARMS_USING_M4, "player0ArmsUsingM4"},
		   { EntityStatus::BODY_IDLE, "player0BodyIdle"},
		   { EntityStatus::HEAD_ANGRY, "player0HeadAngry"},
		   { EntityStatus::HEAD_IDLE, "player0HeadIdle"},
		   { EntityStatus::HEAD_SATISFIED, "player0HeadSatisfied"},
		   { EntityStatus::HEAD_TIRED, "player0HeadTired"},
		   { EntityStatus::LEGS_MOVING_AROUND, "player0LegsMovingAround"},
		   { EntityStatus::LEGS_NOT, "player0LegsNot"}
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

	if (dynamic_cast<Explosion*>(&other))
		return;

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
	else if (dynamic_cast<Door*>(&other) != nullptr)
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
	else if (dynamic_cast<Bullet*>(&other) != nullptr)
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

		this->health -= dynamic_cast<Bullet*>(&other)->getDamage();
		this->health = std::max(0.0, this->health);
	}
	else if (dynamic_cast<CollidableEntity*>(&other) != nullptr) // TODO: aici intra in calcul si bullets !!!!
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
	this->isTired = false;
	this->isWalking = false;
	this->isRunning = false;

	// weapon
	this->weapons[this->currentWeaponIndex]->update();

	if (this->isShooting)
	{
		this->weapons[this->currentWeaponIndex]->onClick();
	}

	// head
	if (this->statuses[3] == EntityStatus::HEAD_TIRED)
	{
		this->isTired = true;

		this->stamina += this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
		this->stamina = std::min(this->stamina, this->staminaCap);

		if (this->stamina == this->staminaCap)
		{
			this->isTired = false;

			updateStatus(EntityStatus::HEAD_IDLE, 3);
		}
	}

	if (this->isTired)
	{
		updateStatus(EntityStatus::LEGS_NOT, 0);

		if (this->statuses[1] == EntityStatus::ARMS_MOVING_AHEAD ||
			this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_WALKING ||
			this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_RUNNING)
			updateStatus(EntityStatus::ARMS_NOT, 1);

		updateStatus(EntityStatus::BODY_IDLE, 2);
	}

	// body (nu avem nimic, o singura animatie de un frame, atat)

	// arms
	if (!this->isTired && (this->moveUpUsed == true || this->moveDownUsed == true
		|| this->moveRightUsed == true || this->moveLeftUsed == true))
	{
		if (this->runUsed == false)
		{
			this->isWalking = true;

			updateStatus(EntityStatus::LEGS_NOT, 0);
			if (this->statuses[1] == EntityStatus::ARMS_MOVING_AHEAD ||
				this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_WALKING ||
				this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_RUNNING)
				updateStatus(EntityStatus::ARMS_MOVING_AROUND_WALKING, 1);
			updateStatus(EntityStatus::BODY_IDLE, 2);
		}
		else
		{
			this->isRunning = true;

			updateStatus(EntityStatus::LEGS_MOVING_AROUND, 0);
			if (this->statuses[1] == EntityStatus::ARMS_MOVING_AHEAD ||
				this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_WALKING ||
				this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_RUNNING)
				updateStatus(EntityStatus::ARMS_MOVING_AROUND_RUNNING, 1);
			updateStatus(EntityStatus::BODY_IDLE, 2);

			this->stamina -= this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
			this->stamina = std::max(0.0, this->stamina);

			if (this->stamina == 0.0)
			{
				updateStatus(EntityStatus::HEAD_TIRED, 3);
			}
		}
	}
	else // IDLE
	{
		updateStatus(EntityStatus::LEGS_NOT, 0);
		if (this->statuses[1] == EntityStatus::ARMS_MOVING_AHEAD ||
			this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_WALKING ||
			this->statuses[1] == EntityStatus::ARMS_MOVING_AROUND_RUNNING)
			updateStatus(EntityStatus::ARMS_MOVING_AHEAD, 1);
		updateStatus(EntityStatus::BODY_IDLE, 2);

		this->stamina += this->staminaChangeSpeed * GlobalClock::get().getDeltaTime();
		this->stamina = std::min(this->stamina, this->staminaCap);
	}

	if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::FIST)
	{
		// TODO: atac pumn
		if (this->weapons[this->currentWeaponIndex]->recentlyShot())
		{
			updateStatus(EntityStatus::ARMS_USING_FIST, 1);
		}
		else if (this->statuses[1] != EntityStatus::ARMS_MOVING_AHEAD &&
			this->statuses[1] != EntityStatus::ARMS_MOVING_AROUND_WALKING &&
			this->statuses[1] != EntityStatus::ARMS_MOVING_AROUND_RUNNING)
		{
			updateStatus(EntityStatus::ARMS_MOVING_AHEAD, 1);
		}
	}
	else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::KNIFE)
	{
		if (this->weapons[this->currentWeaponIndex]->recentlyShot())
		{
			updateStatus(EntityStatus::ARMS_USING_KNIFE, 1);
		}
		else
		{
			updateStatus(EntityStatus::ARMS_HOLDING_KNIFE, 1);
		}
	}
	else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::REVOLVER)
	{
		if (!this->weapons[this->currentWeaponIndex]->stillReloading())
		{
			if (this->weapons[this->currentWeaponIndex]->recentlyShot())
			{
				updateStatus(EntityStatus::ARMS_USING_PISTOL, 1);
			}
			else
			{
				updateStatus(EntityStatus::ARMS_HOLDING_PISTOL, 1);
			}
		}
		else
		{
			updateStatus(EntityStatus::ARMS_RELOADING_PISTOL, 1);
		}
	}
	else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::SHOTGUN)
	{
		if (!this->weapons[this->currentWeaponIndex]->stillReloading())
		{
			if (this->weapons[this->currentWeaponIndex]->recentlyShot())
			{
				updateStatus(EntityStatus::ARMS_USING_SHOTGUN, 1);
			}
			else
			{
				updateStatus(EntityStatus::ARMS_HOLDING_SHOTGUN, 1);
			}
		}
		else
		{
			updateStatus(EntityStatus::ARMS_RELOADING_SHOTGUN, 1);
		}
	}
	else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::AK47)
	{
		if (!this->weapons[this->currentWeaponIndex]->stillReloading())
		{
			if (this->weapons[this->currentWeaponIndex]->recentlyShot())
			{
				updateStatus(EntityStatus::ARMS_USING_AK47, 1);
			}
			else
			{
				updateStatus(EntityStatus::ARMS_HOLDING_AK47, 1);
			}
		}
		else
		{
			updateStatus(EntityStatus::ARMS_RELOADING_AK47, 1);
		}
	}
	else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::M4)
	{
		if (!this->weapons[this->currentWeaponIndex]->stillReloading())
		{
			if (this->weapons[this->currentWeaponIndex]->recentlyShot())
			{
				updateStatus(EntityStatus::ARMS_USING_M4, 1);
			}
			else
			{
				updateStatus(EntityStatus::ARMS_HOLDING_M4, 1);
			}
		}
		else
		{
			updateStatus(EntityStatus::ARMS_RELOADING_M4, 1);
		}
	}
	else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::GRENADE)
	{
		if (!this->weapons[this->currentWeaponIndex]->stillReloading())
		{
			if (this->weapons[this->currentWeaponIndex]->recentlyShot())
			{
				updateStatus(EntityStatus::ARMS_USING_GRENADE, 1);
			}
			else
			{
				updateStatus(EntityStatus::ARMS_HOLDING_GRENADE, 1);
			}
		}
		else
		{
			//updateStatus(EntityStatus::ARMS_RELOADING_GRENADE, 1);
			//updateStatus(EntityStatus::ARMS_USING_GRENADE, 1);
			updateStatus(EntityStatus::ARMS_HOLDING_GRENADE, 1);
		}
	}
	// else if (this->weapons[this->currentWeaponIndex]->getWeaponType() == Weapon::WeaponType::MINIGUN)	// TODO

	// Sound
	SoundManager::get().pause("walking");
	SoundManager::get().pause("running");
	//SoundManager::get().pause("tired");
	if (this->isTired)
	{
		// TODO: adaugat resume aici pt sound effect tired
	}
	else if (this->isWalking)
	{
		SoundManager::get().resume("walking");
	}
	else if (this->isRunning)
	{
		SoundManager::get().resume("running");
	}

	if (this->isTired)
	{
		return;
	}

	double currentSpeed = this->speed;

	if (this->isRunning)
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
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Released, std::bind(&Player::moveUpReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Pressed, std::bind(&Player::moveDown, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Released, std::bind(&Player::moveDownReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Pressed, std::bind(&Player::moveRight, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Released, std::bind(&Player::moveRightReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Pressed, std::bind(&Player::moveLeft, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Released, std::bind(&Player::moveLeftReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("RUN", InputEvent::IE_Pressed, std::bind(&Player::run, this));
	InputHandler::getPlayerInputComponent().bindAction("RUN", InputEvent::IE_Released, std::bind(&Player::runReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("SHOOT", InputEvent::IE_Pressed, std::bind(&Player::shoot, this));
	InputHandler::getPlayerInputComponent().bindAction("SHOOT", InputEvent::IE_Released, std::bind(&Player::stopShooting, this));

	InputHandler::getPlayerInputComponent().bindAction("RELOAD", InputEvent::IE_Pressed, std::bind(&Player::reload, this));

	InputHandler::getPlayerInputComponent().bindAxis(std::bind(&Player::look, this, std::placeholders::_1, std::placeholders::_2));

	InputHandler::getPlayerInputComponent().bindAction("PAUSE", InputEvent::IE_Pressed, std::bind(&Player::pauseGame, this));

	InputHandler::getPlayerInputComponent().bindAction("INTERACT", InputEvent::IE_Pressed, std::bind(&Player::interact, this));
	InputHandler::getPlayerInputComponent().bindAction("INTERACT", InputEvent::IE_Released, std::bind(&Player::interactReleased, this));

	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_1", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot1, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_2", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot2, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_3", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot3, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_4", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot4, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_5", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot5, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_6", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot6, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_7", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot7, this));
	InputHandler::getPlayerInputComponent().bindAction("WEAPON_SLOT_8", InputEvent::IE_Pressed, std::bind(&Player::weaponSlot8, this));

	// shop test
	InputHandler::getPlayerInputComponent().bindAction("SHOP", InputEvent::IE_Pressed, std::bind(&Player::enterShop, this));
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
	this->weapons[this->currentWeaponIndex]->onClick();

	if (4 <= currentWeaponIndex && currentWeaponIndex <= 6)
	{
		this->isShooting = true;
	}
}

void Player::stopShooting()
{
	this->isShooting = false;
}

void Player::reload()
{
	std::cout << "RELOAD" << std::endl;
	this->weapons[this->currentWeaponIndex]->reload();
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
	MenuManager::get().push(PauseMenu::get());
	// PauseMenu::get().setIsInGame(false);
	// PauseMenu::get().setupPauseMenuInputComponent();
	InputHandler::setInputComponent(InputHandler::getMenuInputComponent());
}

void Player::weaponSlot1()
{
	this->isShooting = false;

	if (this->weapons[0] != nullptr && this->currentWeaponIndex != 0)
	{
		weapons[0]->drawWeapon();
		this->currentWeaponIndex = 0;
	}
}

void Player::weaponSlot2()
{
	this->isShooting = false;

	if (this->weapons[1] != nullptr && this->currentWeaponIndex != 1)
	{
		weapons[1]->drawWeapon();
		this->currentWeaponIndex = 1;
	}
}

void Player::weaponSlot3()
{
	this->isShooting = false;

	if (this->weapons[2] != nullptr && this->currentWeaponIndex != 2)
	{
		weapons[2]->drawWeapon();
		this->currentWeaponIndex = 2;
	}
}

void Player::weaponSlot4()
{
	this->isShooting = false;

	if (this->weapons[3] != nullptr && this->currentWeaponIndex != 3)
	{
		weapons[3]->drawWeapon();
		this->currentWeaponIndex = 3;
	}
}

void Player::weaponSlot5()
{
	this->isShooting = false;

	if (this->weapons[4] != nullptr && this->currentWeaponIndex != 4)
	{
		weapons[4]->drawWeapon();
		this->currentWeaponIndex = 4;
	}
}

void Player::weaponSlot6()
{
	this->isShooting = false;

	if (this->weapons[5] != nullptr && this->currentWeaponIndex != 5)
	{
		weapons[5]->drawWeapon();
		this->currentWeaponIndex = 5;
	}
}

void Player::weaponSlot7()
{
	this->isShooting = false;

	if (this->weapons[6] != nullptr && this->currentWeaponIndex != 6)
	{
		weapons[6]->drawWeapon();
		this->currentWeaponIndex = 6;
	}
}

void Player::weaponSlot8()
{
	this->isShooting = false;

	if (this->weapons[7] != nullptr && this->currentWeaponIndex != 7)
	{
		weapons[7]->drawWeapon();
		this->currentWeaponIndex = 7;
	}
}

void Player::draw()
{
	if (this->isDead())
	{
		int deadTextureIndex = (int)(Random::random01() > 0.5);
		double deadRotateAngle = (Random::random01() * 360.0 - Random::EPSILON);
		double deadResize = 1.25;

		std::map<AnimatedEntity::EntityStatus, std::string> m0 = {
			{EntityStatus::DEAD_HUMAN, "player" + std::to_string(deadTextureIndex) + "Dead"}
		};
		std::vector<AnimatedEntity::EntityStatus> v0 = { AnimatedEntity::EntityStatus::DEAD_HUMAN };

		Game::get().addDeadBody(std::make_shared<DeadBody>
			(this->x, this->y, deadResize * this->drawWidth, deadResize * this->drawHeight, deadRotateAngle, 0.0, m0, v0));

		// this->setDeleteEntity(true);

		glfwSetWindowShouldClose(WindowManager::get().getWindow(), true); // TODO: de schimbat
	}
	else if (this->isWalking)
	{
		for (int i = 0; i < this->statuses.size(); ++i)
			SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->statuses[i]]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth + this->walkingOffsetSize * glm::sin(this->walkingOffsetSpeed * GlobalClock::get().getCurrentTime()), this->drawHeight + this->walkingOffsetSize * glm::sin(this->walkingOffsetSpeed * GlobalClock::get().getCurrentTime())), this->rotateAngle);
	}
	else if (this->isRunning)
	{
		for (int i = 0; i < this->statuses.size(); ++i)
			SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->statuses[i]]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth + this->runningOffsetSize * glm::sin(this->runningOffsetSpeed * GlobalClock::get().getCurrentTime()), this->drawHeight + this->runningOffsetSize * glm::sin(this->runningOffsetSpeed * GlobalClock::get().getCurrentTime())), this->rotateAngle);
	}
	else
	{
		for (int i = 0; i < this->statuses.size(); ++i)
			SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->statuses[i]]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timesSinceStatuses[i]), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth, this->drawHeight), this->rotateAngle);
	}
}

void Player::modifyBullets(Weapon::WeaponType weaponType, int amount)
{
	bullets[weaponType] += amount;
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


void Player::enterShop()
{
	MenuManager::get().push(ShopMenuWeapons::get());
	InputHandler::setInputComponent(InputHandler::getMenuInputComponent());
}

