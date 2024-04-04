#include "Weapon.h"

Weapon::Weapon(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double rotateAngle, double damage, double fireRate, int numBullets) :
	RotatableEntity(x, y, textureName, drawWidth, drawHeight, rotateAngle), damage(damage), fireRate(fireRate), numBullets(numBullets)
{

}

Weapon::~Weapon()
{

}