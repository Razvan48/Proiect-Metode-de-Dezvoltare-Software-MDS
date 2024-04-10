#include "Enemy.h"

Enemy::Enemy(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D, double health, double stamina, double armor) :
	Human(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight, animationsName2D, health, stamina, armor), AIEntity(x, y, drawWidth, drawHeight, rotateAngle, speed)
{

}

Enemy::~Enemy()
{

}