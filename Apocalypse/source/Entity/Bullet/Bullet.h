#pragma once

#include "../CollidableEntity.h"
#include "../TexturableEntity.h"

class Bullet : public virtual CollidableEntity, public virtual TexturableEntity
{
protected:

	double damage;

public:

	Bullet(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double damage);
	virtual ~Bullet();
};