#include "Bullet.h"

Bullet::Bullet(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double damage) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed), 
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight), TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D), damage(damage)
{

}

Bullet::~Bullet()
{

}