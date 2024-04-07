#include "Weapon.h"

Weapon::Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D, double fireRate, int numBullets, double damage) :
	TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D), InteractiveEntity(x, y, drawWidth, drawHeight, rotateAngle, speed), fireRate(fireRate), numBullets(numBullets), damage(damage)
{

}


Weapon::~Weapon()
{

}