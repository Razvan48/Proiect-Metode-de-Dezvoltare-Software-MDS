#include "AnimatedEntity.h"

#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

#include "../GlobalClock/GlobalClock.h"

#include "../Camera/Camera.h"

AnimatedEntity::AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::map<EntityStatus, std::string>& animationsName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed), animationsName2D(animationsName2D), timeSinceStatus(GlobalClock::get().getCurrentTime()), status(EntityStatus::IDLE)
{

}

void AnimatedEntity::draw()
{
	if (this->animationsName2D.find(this->status) == this->animationsName2D.end())
	{
		// exceptii
	}
	else
	{
		SpriteRenderer::get().draw(ResourceManager::getShader("sprite"), ResourceManager::getFlipbook(this->animationsName2D[this->status]).getTextureAtTime(GlobalClock::get().getCurrentTime() - this->timeSinceStatus), Camera::get().screenPosition(this->x, this->y), Camera::get().screenSize(this->drawWidth, this->drawHeight), this->rotateAngle);
	}
}

void AnimatedEntity::updateStatus(EntityStatus newStatus)
{
	if (this->status != newStatus)
	{
		this->timeSinceStatus = GlobalClock::get().getCurrentTime();
	}

	this->status = newStatus;
}

AnimatedEntity::~AnimatedEntity()
{

}

