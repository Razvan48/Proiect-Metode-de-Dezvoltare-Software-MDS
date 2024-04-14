#pragma once

#include "string"

#include "Entity.h"

class TexturableEntity : public virtual Entity
{
protected:

	const std::string textureName2D;

public:

	TexturableEntity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, const std::string& textureName2D);
	void draw() override;
	virtual ~TexturableEntity();
};