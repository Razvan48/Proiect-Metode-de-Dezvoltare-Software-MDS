#pragma once

class PlayerTest
{
public:
	PlayerTest() = default;
	~PlayerTest() = default;

	void setupPlayerInputComponent();

	void moveUp();
	void moveDown();
	void moveRight();
	void moveLeft();
};

