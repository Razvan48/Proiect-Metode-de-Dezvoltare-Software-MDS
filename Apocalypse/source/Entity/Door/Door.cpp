#include "Door.h"

Door::Door(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string> animationsName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed),
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight),
	AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D)
{

}

void Door::onCollide(CollidableEntity& other, glm::vec2 overlap)
{

}

Door::~Door()
{

}