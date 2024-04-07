#pragma once

#include "../Entity/TexturableEntity.h"
#include "../Entity/InteractiveEntity.h"

class Weapon : public virtual TexturableEntity, public virtual InteractiveEntity
{
protected:

	double fireRate;
	int numBullets;
	double damage;

public:

	Weapon(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D, double fireRate, int numBullets, double damage);
	virtual ~Weapon();
};

