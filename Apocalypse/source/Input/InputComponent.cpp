#include "InputComponent.h"

#include <iostream> // TODO: delete
#include <fstream>

void InputComponent::bindAction(const std::string& actionName, const InputEvent& keyEvent, const std::function<void()>& func)
{
	std::ifstream fin("config/input.ini");

	std::string action, s;
	int key;

	while (fin >> action >> s >> key)
	{
		if (action == actionName)
		{
			std::cout << action << ' ' << s << ' ' << key << std::endl;
			keyFunctionCallbacks[key][static_cast<int>(keyEvent)].push_back(func);
		}
	}
}

void InputComponent::bindAxis(const std::function<void(double, double)>& func)
{
	mouseFunctionCallbacks.push_back(func);
}

void InputComponent::callbackAction(int key, int action)
{
	for (const auto& f : keyFunctionCallbacks[key][action])
	{
		f();
	}
}

void InputComponent::callbackAxis(double xpos, double ypos)
{
	for (const auto& f : mouseFunctionCallbacks)
	{
		f(xpos, ypos);
	}
}

