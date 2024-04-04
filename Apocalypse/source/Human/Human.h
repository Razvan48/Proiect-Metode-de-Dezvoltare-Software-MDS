#pragma once

#include "../CollidableEntity/CollidableEntity.h"
#include "../RotatableEntity/RotatableEntity.h"
#include "../MovableEntity/MovableEntity.h"

class Human : public CollidableEntity, public MovableEntity
{

private:

public:

	Human(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double collideWidth, double collideHeight, double moveSpeed);
	virtual ~Human();
};