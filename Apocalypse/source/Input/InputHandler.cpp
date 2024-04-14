#include "InputHandler.h"

// instantiate static variables
std::map<int, int> InputHandler::keys;
std::map<int, int> InputHandler::mouseButtons;
std::pair<double, double> InputHandler::mousePosition;
InputComponent InputHandler::playerInputComponent;
InputComponent InputHandler::meniuInputComponent;
InputComponent* InputHandler::activeInputComponent = nullptr;

void InputHandler::setKey(const int& key, const int& value)
{
	keys[key] = value;
}

void InputHandler::setMouseButtons(const int& key, const int& value)
{
	mouseButtons[key] = value;
}

void InputHandler::setMousePosition(const std::pair<double, double>& pos)
{
	mousePosition = pos;
}

void InputHandler::callbackAction(int key, int action)
{
	// TODO: refactor

	if (activeInputComponent)
	{
		activeInputComponent->callbackAction(key, action);
	}
}

void InputHandler::callbackAxis(double xpos, double ypos)
{
	if (activeInputComponent)
	{
		activeInputComponent->callbackAxis(xpos, ypos);
	}
}

void InputHandler::update()
{
	// TODO: Pressed/Repeat

	for (const auto& key : keys)
	{
		if (key.second == 1 || key.second == 2)
		{
			activeInputComponent->callbackAction(key.first, key.second);
		}
	}

	for (const auto& key : mouseButtons)
	{
		if (key.second == 1 || key.second == 2)
		{
			activeInputComponent->callbackAction(key.first, key.second);
		}
	}
}

