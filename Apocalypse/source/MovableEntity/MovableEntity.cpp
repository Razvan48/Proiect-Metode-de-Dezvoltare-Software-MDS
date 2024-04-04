#include "MovableEntity.h"

MovableEntity::MovableEntity(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double moveSpeed) :
	Entity(x, y, textureName, drawWidth, drawHeight), moveSpeed(moveSpeed)
{

}

MovableEntity::~MovableEntity()
{

}