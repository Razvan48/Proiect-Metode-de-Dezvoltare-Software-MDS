#pragma once

#include "../CollidableEntity.h"
#include "../TexturableEntity.h"
#include "../InteractiveEntity.h"

class HealthArmor : public virtual CollidableEntity, public virtual TexturableEntity, public virtual InteractiveEntity
{
protected:

	double addedArmor;

public:

	HealthArmor(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double addedArmor);
	virtual ~HealthArmor();
};

