#pragma once

#include "Entity.h"

class CollidableEntity : public virtual Entity // Virtual Diamond Inheritance
{
protected:

	double collideWidth;
	double collideHeight;

public:

	CollidableEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight);
	double getCollideWidth() const { return this->collideWidth; }
	double getCollideHeight() const { return this->collideHeight; }
	bool isInCollision(const CollidableEntity& other) const;
	virtual void onCollide() = 0; //collision resolution (virtual, each class implements the resolutions)
	virtual ~CollidableEntity();
};