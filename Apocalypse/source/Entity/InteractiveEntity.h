#pragma once

#include "Entity.h"
#include "EntityStatus/EntityStatus.h"

class InteractiveEntity : public virtual Entity // Virtual Diamond Inheritance
{
protected:

	/*
	* Status status;
	* Status = enum in another file which we include?
	* Make a global enum class which all entities can use and which provides a set of statuses. The specific entity implements the transitions between these states for itself.
	*/

	EntityStatus status;
	double timeSinceStatus;

public:

	InteractiveEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed);
	double getTimeSinceStatus() const { return this->timeSinceStatus; };
	void setTimeSinceStatus(double timeSinceStatus) { this->timeSinceStatus = timeSinceStatus; }
	virtual void update(); // TODO: see how we will use this
	virtual ~InteractiveEntity();
};