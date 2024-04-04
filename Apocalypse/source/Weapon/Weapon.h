#pragma once

#include "../RotatableEntity/RotatableEntity.h"

class Weapon : public RotatableEntity
{
private:

	double damage;
	double fireRate;
	int numBullets;

public:

	Weapon(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double rotateAngle, double damage, double fireRate, int numBullets);
	virtual ~Weapon();
};

