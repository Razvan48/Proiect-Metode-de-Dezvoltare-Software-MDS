#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"
#include "../InteractiveEntity.h"

class Door : public virtual CollidableEntity, public virtual AnimatedEntity, public virtual InteractiveEntity
{
protected:

public:

	Door(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D);
	virtual ~Door();
};

