#include "DeadBody.h"

DeadBody::DeadBody(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::map<EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses)
	: Entity(x, y, drawWidth, drawHeight, rotateAngle, speed)
	, AnimatedEntity(x, y, drawWidth, drawHeight, rotateAngle, speed, animationsName2D, statuses)
{

}

DeadBody::~DeadBody()
{

}