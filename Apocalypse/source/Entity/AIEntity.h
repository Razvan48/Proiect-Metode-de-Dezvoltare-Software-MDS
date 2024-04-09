#pragma once

#include "Entity.h"

class AIEntity : public virtual Entity
{
protected:

public:

	AIEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed);

	virtual void pathFindingTarget() = 0;
	virtual void onTargetReach() = 0;
	virtual void onNearTarget() = 0;

	virtual ~AIEntity();
};