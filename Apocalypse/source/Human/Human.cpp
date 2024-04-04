#include "Human.h"

Human::Human(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double collideWidth, double collideHeight, double moveSpeed) :
	CollidableEntity(x, y, textureName, drawWidth, drawHeight, collideWidth, collideHeight), MovableEntity(x, y, textureName, drawWidth, drawHeight, moveSpeed)
	// TODO: de verificat mostenirea diamant
{

}

Human::~Human()
{

}