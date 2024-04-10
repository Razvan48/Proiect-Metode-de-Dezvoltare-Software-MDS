#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"

class Human : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

	double health;
	double stamina;
	double armor;

public:

	Human(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D, double health, double stamina, double armor);
	virtual ~Human();
};