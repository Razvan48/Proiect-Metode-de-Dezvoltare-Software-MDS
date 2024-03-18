#include "Camera.h"

Camera& Camera::get()
{
	static Camera instance;

	return instance;
}

void Camera::setX(double x)
{
	this->x = x;
}

void Camera::setY(double y)
{
	this->y = y;
}

void Camera::initializeCoords(double x, double y)
{
	this->setX(x);
	this->setY(y);
}

