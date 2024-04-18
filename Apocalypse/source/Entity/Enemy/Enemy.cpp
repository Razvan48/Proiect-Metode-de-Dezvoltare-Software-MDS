#include "Enemy.h"

Enemy::Enemy(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, double health) :
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, health),
	AIEntity(x, y, drawWidth, drawHeight, rotateAngle, speed)
{

}

Enemy::~Enemy()
{

}