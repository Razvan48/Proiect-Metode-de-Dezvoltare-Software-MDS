#pragma once

#include "../CollidableEntity.h"
#include "../TexturableEntity.h"

class Weapon : public virtual CollidableEntity, public virtual TexturableEntity
{
protected:

	double fireRate;
	int numBullets;
	double damage;

public:

	Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double fireRate, int numBullets, double damage);
	virtual ~Weapon();
};

