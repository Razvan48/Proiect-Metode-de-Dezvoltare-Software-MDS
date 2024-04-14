#pragma once

#include <vector>
#include "string"

#include "Entity.h"

class AnimatedEntity : public virtual Entity // Virtual Diamond Inheritance
{
protected:

	const std::vector<std::string> animationsName2D;

	enum class EntityStatus
	{
		DEFAULT, //asta doar debug, NU FOLOSIM DEFAULT, FOLOSIM IDLE PENTRU STATUS DE INCEPUT
		IDLE,
		Walking,
		Running,
		TIRED,
		DYING,
		HOVERED,
		CLICKED
	};

	EntityStatus status;
	double timeSinceStatus;

public:

	AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::vector<std::string>& animationsName2D);
	void draw() override;
	double getTimeSinceStatus() const { return this->timeSinceStatus; };
	void setTimeSinceStatus(double timeSinceStatus) { this->timeSinceStatus = timeSinceStatus; }
	virtual void update() = 0;
	virtual ~AnimatedEntity();
};