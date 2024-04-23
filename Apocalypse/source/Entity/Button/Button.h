#pragma once

#include "../CollidableEntity.h"
#include "../AnimatedEntity.h"

#include <map>

class Button : public virtual CollidableEntity, public virtual AnimatedEntity
{
protected:
	std::string label;

public:

	Button(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed, double collideWidth, double collideHeight, const std::map<AnimatedEntity::EntityStatus, std::string>& animationsName2D);
	virtual ~Button();

	void onCollide(CollidableEntity& other, glm::vec2 overlap) override;
	void update() override;
	
	std::string getLabel() const { return label; }
	void setLabel(const std::string& label) { this->label = label; }

	void draw() override;

	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
};