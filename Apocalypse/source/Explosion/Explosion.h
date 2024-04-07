#pragma once

#include "../Entity/CollidableEntity.h"
#include "../Entity/AnimatedEntity.h"

class Explosion : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

	// TODO: ceva in plus

public:

	Explosion(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D);
	virtual ~Explosion();
};

