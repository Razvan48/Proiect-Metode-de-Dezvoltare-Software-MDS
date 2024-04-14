#include "Weapon.h"

Weapon::Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double fireRate, int numBullets, double damage) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D),
	fireRate(fireRate), numBullets(numBullets), damage(damage)
{

}


Weapon::~Weapon()
{

}