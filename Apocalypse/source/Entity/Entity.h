#pragma once

#include <string>

class Entity
{
protected:

	double x;
	double y;
	double drawWidth;
	double drawHeight;
	double rotateAngle;
	double speed;

public:

	Entity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed);
	virtual void draw() = 0;
	double getX() const { return this->x; }
	double getY() const { return this->y; }
	double getDrawWidth() const { return this->drawWidth; }
	double getDrawHeight() const { return this->drawHeight; }
	double getRotateAngle() const { return this->rotateAngle; }
	double getSpeed() const { return this->speed; }
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	void setRotateAngle(double rotateAngle) { this->rotateAngle = rotateAngle; }
	void setSpeed(double speed) { this->speed = speed; }
	virtual ~Entity();
};