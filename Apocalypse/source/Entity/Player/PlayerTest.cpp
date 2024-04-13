#include "PlayerTest.h"

#include "../../Input/InputHandler.h"

#include <iostream> // TODO: delete

void PlayerTest::setupPlayerInputComponent()
{
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Pressed, std::bind(&PlayerTest::moveUp, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_UP", InputEvent::IE_Repeat, std::bind(&PlayerTest::moveUp, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Pressed, std::bind(&PlayerTest::moveDown, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_DOWN", InputEvent::IE_Repeat, std::bind(&PlayerTest::moveDown, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Pressed, std::bind(&PlayerTest::moveRight, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_RIGHT", InputEvent::IE_Repeat, std::bind(&PlayerTest::moveRight, this));

	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Pressed, std::bind(&PlayerTest::moveLeft, this));
	InputHandler::getPlayerInputComponent().bindAction("MOVE_LEFT", InputEvent::IE_Repeat, std::bind(&PlayerTest::moveLeft, this));
}

void PlayerTest::moveUp()
{
	std::cout << "move up" << std::endl;
}

void PlayerTest::moveDown()
{
	std::cout << "move down" << std::endl;
}

void PlayerTest::moveRight()
{
	std::cout << "move right" << std::endl;
}

void PlayerTest::moveLeft()
{
	std::cout << "move left" << std::endl;
}

