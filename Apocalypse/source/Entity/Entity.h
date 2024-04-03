#pragma once

#include <string>

class Entity
{
private:

	double x;
	double y;
	const std::string textureName;
	double drawWidth;
	double drawHeight;
	double rotate;

public:

	Entity(double x, double y, const std::string textureName, double drawWidth, double drawHeight);
	virtual void draw();
	double getX() { return this->x; }
	double getY() { return this->y; }
	double getDrawWidth() { return this->drawWidth; }
	double getDrawHeight() { return this->drawHeight; }
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	virtual ~Entity();
};