#pragma once

#include "../Human/Human.h"
#include "../AIEntity.h"

class Enemy : public virtual Human, public virtual AIEntity
{
private:


public:

	Enemy(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, double health);
	~Enemy();
};