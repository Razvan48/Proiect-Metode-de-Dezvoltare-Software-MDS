#pragma once

#include "../CollidableEntity.h"
#include "../TexturableEntity.h"
#include "../InteractiveEntity.h"

class Wall : public virtual CollidableEntity, public virtual TexturableEntity, public virtual InteractiveEntity
{
protected:

public:

	Wall(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D);
	virtual ~Wall();
};