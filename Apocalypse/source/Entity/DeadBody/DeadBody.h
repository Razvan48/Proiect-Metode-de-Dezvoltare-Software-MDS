#pragma once

#include "../AnimatedEntity.h"

class DeadBody : public virtual AnimatedEntity
{
protected:

public:

	DeadBody(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::map<EntityStatus, std::string>& animationsName2D, const std::vector<EntityStatus>& statuses);
	virtual ~DeadBody();
};