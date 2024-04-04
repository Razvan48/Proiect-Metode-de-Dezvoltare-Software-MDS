#include "RotatableEntity.h"

RotatableEntity::RotatableEntity(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double rotateAngle) :
	Entity(x, y, textureName, drawWidth, drawHeight), rotateAngle(rotateAngle)
{

}

RotatableEntity::~RotatableEntity()
{

}