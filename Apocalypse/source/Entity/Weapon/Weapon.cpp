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

void Weapon::onClick() // TODO: mai trb adaugate chestii
{
	if (this->weaponType == WeaponType::FIST)
		return;

	if (this->weaponType == WeaponType::PISTOL && GlobalClock::get().getCurrentTime() - this->timeSinceLastShot > 0.0)
	{
		this->timeSinceLastShot = GlobalClock::get().getCurrentTime();

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, glm::vec3(Camera::get().screenPosition(Player::get().getX(), Player::get().getY()), 0.0f));
		model = glm::rotate(model, glm::radians(static_cast<float>(Player::get().getRotateAngle())), glm::vec3(0.0f, 0.0f, 1.0f));

		glm::vec4 bulletRelativeLocation = model * glm::vec4(0.4f, 0.4f, 0.0f, 0.0f);	// TODO: change offset.x and offset.y
		glm::vec2 bulletLocation = glm::vec2(
			Player::get().getX() + bulletRelativeLocation.x,
			Player::get().getY() + bulletRelativeLocation.y
		);

		SoundManager::get().play("pistolShot", false); //TODO: de schimbat in ceva mai general sound effect-ul

		Game::get().addEntity(std::make_shared<Bullet>(static_cast<double>(bulletLocation.x), static_cast<double>(bulletLocation.y), 0.3, 0.3, Player::get().getRotateAngle(), 10.0, 0.3, 0.3, "bullet0", 20.0)); // TODO: change speed + textura bullet (mai multe probleme)

		Player::get().updateStatus(AnimatedEntity::EntityStatus::ARMS_USING_PISTOL, 1);
	}
	else
	{
		Player::get().updateStatus(AnimatedEntity::EntityStatus::ARMS_RELOADING_PISTOL, 1);
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


Weapon::~Weapon()
{

}