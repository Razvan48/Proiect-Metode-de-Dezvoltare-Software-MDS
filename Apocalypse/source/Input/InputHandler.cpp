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

void InputHandler::callback(int key, int action)
{
	// TODO: refactor

	if (activeInputComponent)
	{
		activeInputComponent->callback(key, action);
	}
}

void InputHandler::update()
{
	// TODO

	for (const auto& key : keys)
	{
		if (key.second == 1 || key.second == 2)
		{
			activeInputComponent->callback(key.first, key.second);
		}
	}

	for (const auto& key : mouseButtons)
	{
		if (key.second == 1 || key.second == 2)
		{
			activeInputComponent->callback(key.first, key.second);
		}
	}
}

