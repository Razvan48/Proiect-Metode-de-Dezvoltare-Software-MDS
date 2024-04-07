#pragma once

#include "../Entity/CollidableEntity.h"
#include "../Entity/AnimatedEntity.h"
#include "../Entity/InteractiveEntity.h"

class Wall : public virtual CollidableEntity, public virtual AnimatedEntity, public virtual InteractiveEntity
{
protected:

private:

	Wall(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D);
	virtual ~Wall();
};