#include "Button.h"

Button::Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::vector<std::string>& animationsName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight), AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D),
	InteractiveEntity(x, y, drawWidth, drawHeight, rotateAngle, speed)
{

}


Button::~Button()
{

}