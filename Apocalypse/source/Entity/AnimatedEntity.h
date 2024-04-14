#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.h"

#include "../GlobalClock/GlobalClock.h"

class AnimatedEntity : public virtual Entity
{
protected:

	enum class EntityStatus
	{
		DEFAULT, //asta doar debug, NU FOLOSIM DEFAULT, FOLOSIM IDLE PENTRU STATUS DE INCEPUT
		IDLE,
		WALKING,
		RUNNING,
		TIRED,
		DYING,
		HOVERED,
		CLICKED
	};

private:

	EntityStatus status;
	double timeSinceStatus;

protected:

	std::map<EntityStatus, std::string> animationsName2D;

public:

	AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::map<EntityStatus, std::string>& animationsName2D);
	void draw() override;
	double getTimeSinceStatus() const { return this->timeSinceStatus; };
	void setTimeSinceStatus(double timeSinceStatus) { this->timeSinceStatus = timeSinceStatus; }
	EntityStatus getStatus() const { return this->status; }
	void updateStatus(EntityStatus newStatus);
	virtual void update() = 0;
	virtual ~AnimatedEntity();
};