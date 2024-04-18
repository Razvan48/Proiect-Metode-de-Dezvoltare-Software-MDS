#include "Camera.h"

#include "../Entity/Player/Player.h"

Camera::Camera() : // release zoom 112.0, debug zoom 128.0
	x(0.0), y(0.0), zoom(128.0), followsPlayer(false)
{
	// TODO: trebuie?
	//Player::get();
}

Camera& Camera::get()
{
	static Camera instance;

	return instance;
}

void Camera::update()
{
	if (this->followsPlayer)
	{
		this->x = Player::get().getX();
		this->y = Player::get().getY();
	}
	else
	{
		this->x = 0.0;
		this->y = 0.0;
	}
}

glm::vec2 Camera::screenPosition(double x, double y) const
{
	return glm::vec2((x - this->x) * this->zoom, (y - this->y) * this->zoom);
}

glm::vec2 Camera::screenSize(double width, double height) const
{
	return glm::vec2(width * this->zoom, height * this->zoom);
}
