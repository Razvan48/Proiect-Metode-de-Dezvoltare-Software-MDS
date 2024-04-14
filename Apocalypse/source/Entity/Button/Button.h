#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"

#include <map>

class Button : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

public:

	Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D);
	virtual ~Button();
};