#include "Wall.h"

Wall::Wall(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D) :
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight), AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D), InteractiveEntity(x, y, drawWidth, drawHeight, rotateAngle, speed)
{

}


Wall::~Wall()
{

}