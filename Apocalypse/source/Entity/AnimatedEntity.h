#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.h"

#include "../GlobalClock/GlobalClock.h"

class AnimatedEntity : public virtual Entity
{
	friend class MainMenu;

public:

	static enum class EntityStatus
	{
		DEFAULT, //asta doar debug, NU FOLOSIM DEFAULT, FOLOSIM IDLE PENTRU STATUS DE INCEPUT
		IDLE,
		WALKING,
		RUNNING,
		TIRED,
		DYING,
		OPENED,
		HOVERED,
		CLICKED,

		/*
		BODY_IDLE,
		ARMS_IDLE,
		LEGS_IDLE,
		ARMS_WALKING,
		ARMS_RUNNING,
		HEAD_IDLE,
		HEAD_TIRED,
		LEGS_RUNNING,
		*/
	};

protected:
	EntityStatus status;
	double timeSinceStatus;

	std::map<EntityStatus, std::string> animationsName2D;

public:

	AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::map<EntityStatus, std::string>& animationsName2D);
	void draw() override;
	double getTimeSinceStatus() const { return this->timeSinceStatus; };
	void setTimeSinceStatus(double timeSinceStatus) { this->timeSinceStatus = timeSinceStatus; }
	EntityStatus getStatus() const { return this->status; }
	void updateStatus(EntityStatus newStatus);
	virtual ~AnimatedEntity();
};