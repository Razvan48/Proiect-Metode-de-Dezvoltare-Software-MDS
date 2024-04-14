#include "InteractiveEntity.h"

#include "../GlobalClock/GlobalClock.h"

InteractiveEntity::InteractiveEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed) :
	Entity(x, y, drawWidth, drawHeight, rotateAngle, speed), timeSinceStatus(GlobalClock::get().getCurrentTime()), status(EntityStatus::IDLE)
{

}

void InteractiveEntity::update()
{

}

InteractiveEntity::~InteractiveEntity()
{

}