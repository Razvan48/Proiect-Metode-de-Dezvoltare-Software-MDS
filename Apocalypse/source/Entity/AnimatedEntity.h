#pragma once

#include <vector>
#include <string>
#include <map>

#include "Entity.h"

#include "../GlobalClock/GlobalClock.h"

class AnimatedEntity : public virtual Entity
{
private:

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

		ARMS_HOLDING_GRENADE,
		ARMS_HOLDING_KNIFE,
		ARMS_HOLDING_PISTOL,
		ARMS_MOVING_AHEAD,
		ARMS_MOVING_AROUND_WALKING,
		ARMS_MOVING_AROUND_RUNNING,
		ARMS_NOT,
		ARMS_RELOADING_PISTOL,
		ARMS_USING_GRENADE,
		ARMS_USING_KNIFE,
		ARMS_USING_PISTOL,

		BODY_IDLE,

		HEAD_ANGRY,
		HEAD_IDLE,
		HEAD_SATISFIED,
		HEAD_TIRED,

		LEGS_MOVING_AROUND,
		LEGS_NOT,
	};

protected:
	std::vector<EntityStatus> statuses;
	std::vector<double> timesSinceStatuses;

	std::map<EntityStatus, std::string> animationsName2D;

public:

	AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::map<EntityStatus, std::string>& animationsName2D, std::vector<EntityStatus> statuses);
	void draw() override;
	double getTimeSinceStatus(int index = 0) const { return this->timesSinceStatuses[index]; };
	void setTimeSinceStatus(double timeSinceStatus, int index = 0) { this->timesSinceStatuses[index] = timeSinceStatus; }
	EntityStatus getStatus(int index = 0) const { return this->statuses[0]; }
	void updateStatus(EntityStatus newStatus, int index = 0);
	virtual ~AnimatedEntity();
};