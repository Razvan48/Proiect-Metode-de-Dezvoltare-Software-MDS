#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"

class Door : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:

public:

	Door(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string> animationsName2D);
	void onCollide(CollidableEntity& other, glm::vec2 overlap) override;
	virtual ~Door();
};

