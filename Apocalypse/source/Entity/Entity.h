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
	bool deleteEntity;

public:
	Entity(double x, double y, double drawWidth, double drawHeight, double rotateAngle, double speed);
	virtual ~Entity();

	virtual void draw() = 0;
	virtual void update(); // virtual, dar nu pur virtual

	inline double getX() const { return this->x; }
	inline double getY() const { return this->y; }
	inline double getDrawWidth() const { return this->drawWidth; }
	inline double getDrawHeight() const { return this->drawHeight; }
	inline double getRotateAngle() const { return this->rotateAngle; }
	inline double getSpeed() const { return this->speed; }
	inline bool getDeleteEntity() const { return deleteEntity; }
	
	inline void setX(double x) { this->x = x; }
	inline void setY(double y) { this->y = y; }
	inline void setRotateAngle(double rotateAngle) { this->rotateAngle = rotateAngle; }
	inline void setSpeed(double speed) { this->speed = speed; }
	inline void setDeleteEntity(bool value) { this->deleteEntity = value; }
};

