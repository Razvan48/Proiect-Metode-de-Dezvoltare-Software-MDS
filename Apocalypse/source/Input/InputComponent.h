#pragma once

#include <string>
#include <map>
#include <functional>

enum InputEvent
{
	IE_Released = 0,
	IE_Pressed = 1,
	IE_Repeat = 2,
	IE_Default = 3,
};

class InputComponent
{
public:
	void bindAction(const std::string& actionName, const InputEvent& keyEvent, const std::function<void()>& func);
	void bindAxis(const std::function<void(double, double)>& func);

	void callbackAction(int key, int action);
	void callbackAxis(double xpos, double ypos);

private:
	// [key][keyEvent] = vector<> functions
	std::map<int, std::map<int, std::vector<std::function<void()>>>> keyFunctionCallbacks;
	std::vector<std::function<void(double, double)>> mouseFunctionCallbacks;
};

