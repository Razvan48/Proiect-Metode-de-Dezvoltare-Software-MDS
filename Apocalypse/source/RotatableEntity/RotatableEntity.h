#pragma once

#include "../Entity/Entity.h"

class RotatableEntity : virtual public Entity // Virtual Diamond Inheritance
{
private:

	double rotateAngle;

public:

	RotatableEntity(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double rotateAngle);
	double getRotateAngle() { return this->rotateAngle; }
	void setRotateAngle(double rotateAngle) { this->rotateAngle = rotateAngle; }
	virtual ~RotatableEntity();
};