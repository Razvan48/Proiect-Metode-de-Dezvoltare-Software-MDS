#pragma once

#include "Entity.h"

#include <glm/vec2.hpp>

class CollidableEntity : public virtual Entity // Virtual Diamond Inheritance
{
protected:

	double collideWidth;
	double collideHeight;

public:

	CollidableEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight);
	double getCollideWidth() const { return this->collideWidth; }
	double getCollideHeight() const { return this->collideHeight; }
	glm::vec2 isInCollision(const CollidableEntity& other) const;
	virtual void onCollide(CollidableEntity& other, glm::vec2 overlap) = 0; //collision resolution (virtual, each class implements the resolutions)
	virtual ~CollidableEntity();
};