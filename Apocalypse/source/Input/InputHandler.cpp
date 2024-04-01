#include "InputHandler.h"

// instantiate static variables
std::map<int, int> InputHandler::keys;
std::map<int, int> InputHandler::mouseButtons;
std::pair<double, double> InputHandler::mousePosition;

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

