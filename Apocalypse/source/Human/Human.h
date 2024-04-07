#pragma once

#include "../Entity/CollidableEntity.h"
#include "../Entity/AnimatedEntity.h"

class Human : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

	double health;
	double armor;

public:

	Human(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D, double health, double armor);
	virtual ~Human();
};