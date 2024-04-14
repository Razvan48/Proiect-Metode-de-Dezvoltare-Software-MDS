#include "AnimatedEntity.h"

#include "../Renderer/SpriteRenderer.h"
#include "../ResourceManager/ResourceManager.h"

#include "../GlobalClock/GlobalClock.h"

AnimatedEntity::AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::vector<std::string>& animationsName2D) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed), animationsName2D(animationsName2D), timeSinceStatus(GlobalClock::get().getCurrentTime()), status(EntityStatus::IDLE)
{

}

void AnimatedEntity::draw()
{
	// TODO: implementat

}

AnimatedEntity::~AnimatedEntity()
{

}

