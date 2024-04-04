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

public:

	Entity(double x, double y, const std::string textureName, double drawWidth, double drawHeight);
	virtual void draw();
	double getX() const { return this->x; }
	double getY() const { return this->y; }
	double getDrawWidth() const { return this->drawWidth; }
	double getDrawHeight() const { return this->drawHeight; }
	void setX(double x) { this->x = x; }
	void setY(double y) { this->y = y; }
	virtual ~Entity();
};