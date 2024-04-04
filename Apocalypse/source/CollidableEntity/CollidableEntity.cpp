#include "CollidableEntity.h"

CollidableEntity::CollidableEntity(double x, double y, const std::string textureName, double drawWidth, double drawHeight, double collideWidth, double collideHeight) :
	Entity(x, y, textureName, drawWidth, drawHeight), collideWidth(collideWidth), collideHeight(collideHeight)
{

}

bool CollidableEntity::isInCollision(const CollidableEntity& other)
{
	// TODO: de verificat ca l-am scris la 1 noaptea

	double left1 = this->getX() - this->collideWidth / 2.0;
	double right1 = this->getX() + this->collideWidth / 2.0;
	double left2 = other.getX() - other.collideWidth / 2.0;
	double right2 = other.getX() + other.collideWidth / 2.0;

	double down1 = this->getY() - this->collideHeight / 2.0;
	double up1 = this->getY() + this->collideHeight / 2.0;
	double down2 = other.getY() - other.collideHeight / 2.0;
	double up2 = other.getY() + other.collideHeight / 2.0;

	return std::max(left1, left2) <= std::min(right1, right2) && std::max(down1, down2) <= std::min(up1, up2);
}

CollidableEntity::~CollidableEntity()
{

}