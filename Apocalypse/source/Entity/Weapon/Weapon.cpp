#include "Weapon.h"

#include "../../Game/Game.h"
#include "../../Camera/Camera.h"
#include "../../SoundManager/SoundManager.h"

#include "../Player/Player.h"
#include "../../GlobalClock/GlobalClock.h"
#include "../Bullet/Bullet.h"

#include <glm/gtc/matrix_transform.hpp>

Weapon::Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D, double interactionWidth, double interactionHeight, double fireRate, int numBullets, double damage, double reloadTime, WeaponType weaponType, double shortRangeAttackRadius)
	: Entity(x, y, drawWidth, drawHeight, rotateAngle, speed)
	, TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D)
	, InteractiveEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, interactionWidth, interactionHeight)
	, PickUp(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D, interactionWidth, interactionHeight)
	, fireRate(fireRate), numBullets(numBullets), damage(damage), reloadTime(reloadTime), weaponType(weaponType), shortRangeAttackRadius(shortRangeAttackRadius)
	, timeSinceLastShot(GlobalClock::get().getCurrentTime()), timeSinceStartReload(GlobalClock::get().getCurrentTime())
{

}

bool Weapon::isInInteraction()
{
	double left1 = this->getX() - this->interactionWidth / 2.0;
	double right1 = this->getX() + this->interactionWidth / 2.0;
	double left2 = Player::get().getX() - Player::get().getCollideWidth() / 2.0;
	double right2 = Player::get().getX() + Player::get().getCollideWidth() / 2.0;

	double down1 = this->getY() - this->interactionHeight / 2.0;
	double up1 = this->getY() + this->interactionHeight / 2.0;
	double down2 = Player::get().getY() - Player::get().getCollideHeight() / 2.0;
	double up2 = Player::get().getY() + Player::get().getCollideHeight() / 2.0;

	return std::max(left1, left2) <= std::min(right1, right2) && std::max(down1, down2) <= std::min(up1, up2);
}

void Weapon::onInteraction()
{
	// TODO:
}

void Weapon::onClick()
{
	if (numBullets == 0)
	{
		switch (weaponType)
		{
		case Weapon::WeaponType::PISTOL:
			SoundManager::get().play("revolverEmpty", false);
			break;

		case Weapon::WeaponType::SHOTGUN:
			// TODO
			break;

		case Weapon::WeaponType::AK47:
			// TODO
			break;

		case Weapon::WeaponType::M4:
			// TODO
			break;

		case Weapon::WeaponType::MINIGUN:
			// TODO
			break;
		}

		return;
	}

	if (GlobalClock::get().getCurrentTime() - this->timeSinceLastShot <= this->fireRate)
	{
		return;
	}

	this->timeSinceLastShot = GlobalClock::get().getCurrentTime();

	if (this->weaponType == WeaponType::FIST || this->weaponType == WeaponType::KNIFE)
	{
		switch (weaponType)
		{
		case WeaponType::FIST:
			SoundManager::get().play("fist", false);
			break;

		case WeaponType::KNIFE:
			// TODO
			// SoundManager::get().play("pistolShot", false);
			break;
		}
	}
	else // spawn bullet
	{
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(Camera::get().screenPosition(Player::get().getX(), Player::get().getY()), 0.0f));
		model = glm::rotate(model, glm::radians(static_cast<float>(Player::get().getRotateAngle())), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec4 bulletRelativeLocation = model * glm::vec4(0.5f, 0.05f, 0.0f, 0.0f);
		glm::vec2 bulletLocation = glm::vec2(
			Player::get().getX() + bulletRelativeLocation.x,
			Player::get().getY() + bulletRelativeLocation.y
		);

		switch (weaponType)
		{
		case WeaponType::PISTOL:
			SoundManager::get().play("revolver_01", false);
			Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, Player::get().getRotateAngle(), 10.0, 0.3, 0.3, "bullet0", 20.0));
			break;

		case WeaponType::SHOTGUN:
			// TODO
			// SoundManager::get().play("pistolShot", false);
			// Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, Player::get().getRotateAngle(), 10.0, 0.3, 0.3, "bullet0", 20.0));
			break;

		case WeaponType::AK47:
			// TODO
			// SoundManager::get().play("pistolShot", false);
			// Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, Player::get().getRotateAngle(), 10.0, 0.3, 0.3, "bullet0", 20.0));
			break;

		case WeaponType::M4:
			// TODO
			// SoundManager::get().play("pistolShot", false);
			// Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, Player::get().getRotateAngle(), 10.0, 0.3, 0.3, "bullet0", 20.0));
			break;

		case WeaponType::MINIGUN:
			// TODO
			// SoundManager::get().play("pistolShot", false);
			// Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, Player::get().getRotateAngle(), 10.0, 0.3, 0.3, "bullet0", 20.0));
			break;
		}
	}
}

void Weapon::update()
{
	// TODO: aici trb contorizat daca a trecut mai mult timp de la ultima utilizare decat reloadTime-ul, fapt in care posibila animatie de reload se opreste si obiectul redevine utilizabil


	if (this->weaponType == WeaponType::FIST)
		return;

	if (this->weaponType == WeaponType::PISTOL) // TODO: nu e ok deloc
	{

	}
}

void Weapon::drawWeapon()
{
	switch (weaponType)
	{
	case Weapon::WeaponType::FIST:
		break;

	case Weapon::WeaponType::KNIFE:
		break;

	case Weapon::WeaponType::PISTOL:
		SoundManager::get().play("revolverDraw", false);
		break;

	case Weapon::WeaponType::SHOTGUN:
		break;

	case Weapon::WeaponType::AK47:
		break;

	case Weapon::WeaponType::M4:
		break;

	case Weapon::WeaponType::MINIGUN:
		break;
	}
}

