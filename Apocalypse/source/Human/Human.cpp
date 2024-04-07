#include "Human.h"

Human::Human(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D, double health = 100.0, double armor = 0.0) :
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight), AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D), health(health), armor(armor)
{

}

Human::~Human()
{

}

