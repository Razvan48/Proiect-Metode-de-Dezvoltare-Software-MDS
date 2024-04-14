#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"

class Button : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

private:

	Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D);
	virtual ~Button();
};