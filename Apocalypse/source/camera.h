#pragma once

class Camera
{
private:
	Camera() = default;
	~Camera() = default;
	Camera(const Camera& other) = delete;
	Camera& operator= (const Camera& other) = delete;
	Camera(const Camera&& other) = delete;
	Camera& operator= (const Camera&& other) = delete;

private:
	double x;
	double y;

public:
	static Camera& get();
	inline double getX() { return x; };
	inline double getY() { return y; };
	void setX(double x);
	void setY(double y);
	void initializeCoords(double x, double y);
};
