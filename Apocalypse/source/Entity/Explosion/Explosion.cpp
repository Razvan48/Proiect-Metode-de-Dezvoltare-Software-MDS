#include "Explosion.h"
#include <memory>

#include "../../GlobalClock/GlobalClock.h"
#include "../Human/Human.h"

Explosion::Explosion(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses, double explosionDuration, double explosionDamage)
	:Entity(x, y, drawWidth, drawHeight, rotateAngle, speed)
	,CollidableEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, collideWidth, collideHeight)
	,AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D, statuses)
	,explosionStarted(GlobalClock::get().getCurrentTime()), explosionDuration(explosionDuration), explosionDamage(explosionDamage)
{

}

Explosion::~Explosion()
{

}

void Explosion::update()
{
	if (GlobalClock::get().getCurrentTime() - this->explosionStarted > this->explosionDuration)
		this->setDeleteEntity(true);
}

void Explosion::onCollide(CollidableEntity& other, glm::vec2 overlap)
{
	if (dynamic_cast<Human*>(&other))
	{
		dynamic_cast<Human*>(&other)->setHealth(std::max(0.0, dynamic_cast<Human*>(&other)->getHealth() - this->explosionDamage * GlobalClock::get().getDeltaTime()));
	}
}