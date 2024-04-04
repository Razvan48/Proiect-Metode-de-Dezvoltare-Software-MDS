#pragma once

#include "../RotatableEntity/RotatableEntity.h"

class MovableEntity : virtual public RotatableEntity // Virtual Diamond Inheritance // TODO: mai trebuie virtual public aici? (de verificat si in rotatable si collidable)
{
private:

	double moveSpeed;

public:

	MovableEntity(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double moveSpeed);
	double getMoveSpeed() const { return this->moveSpeed; }
	void setMoveSpeed(double moveSpeed) { this->moveSpeed = moveSpeed; }
	virtual ~MovableEntity();
};