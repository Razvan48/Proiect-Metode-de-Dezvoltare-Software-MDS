#pragma once

#include "../Entity/Entity.h"

class CollidableEntity : virtual public Entity // Virtual Diamond Inheritance
{
private:

	double collideWidth;
	double collideHeight;

public:

	CollidableEntity(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double collideWidth, double collideHeight);
	double getCollideWidth() const { return this->collideWidth; }
	double getCollideHeight() const { return this->collideHeight; }
	bool isInCollision(const CollidableEntity& other);
	virtual ~CollidableEntity();
};