#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"

class Human : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

	double health;
	double healthCap;

public:

	double getHealth() const { return this->health; }
	double getHealthCap() const { return this->healthCap; }

	Human(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, double health);
	virtual ~Human();
};