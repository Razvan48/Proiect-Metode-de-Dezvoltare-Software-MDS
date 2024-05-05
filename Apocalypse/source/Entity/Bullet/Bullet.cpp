#include "Bullet.h"

#include "../../GlobalClock/GlobalClock.h"

#include <iostream>	// TODO: debug

Bullet::Bullet(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::string& textureName2D, double damage) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed), 
	CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight), TexturableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, textureName2D), damage(damage)
{

}

void Bullet::onCollide(CollidableEntity& other, glm::vec2 overlap)
{
	std::cout << "On collide" << std::endl;

	setDeleteEntity(true);
}

void Bullet::update()
{
	double velocityX = this->speed * GlobalClock::get().getDeltaTime() * glm::cos(glm::radians(this->rotateAngle));
	double velocityY = this->speed * GlobalClock::get().getDeltaTime() * glm::sin(glm::radians(this->rotateAngle));

	this->x += velocityX;
	this->y += velocityY;
}

