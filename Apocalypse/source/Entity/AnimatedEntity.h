#pragma once

#include <vector>
#include "string"

#include "Entity.h"

class AnimatedEntity : public virtual Entity // Virtual Diamond Inheritance
{
protected:

	const std::vector<std::string> animationsName2D;

	/*
	*  TODO: 
	*  save to which texture from which animation we have arrived to know what to draw?
	*/

public:

	AnimatedEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::vector<std::string>& animationsName2D);
	//void draw() override;
	virtual ~AnimatedEntity();
};