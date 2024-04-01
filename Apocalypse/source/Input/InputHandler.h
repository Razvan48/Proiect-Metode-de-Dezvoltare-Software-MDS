#pragma once

#include <map>

class InputHandler
{
public:
	static inline bool getKey(const int& key) { return keys[key]; }
	static inline bool getMouseButtons(const int& key) { return mouseButtons[key]; }
	static inline std::pair<double, double> getMousePosition() { return mousePosition; }

	static void setKey(const int& key, const int& value);
	static void setMouseButtons(const int& key, const int& value);
	static void setMousePosition(const std::pair<double, double>& pos);

private:
	InputHandler() = default;
	~InputHandler() = default;
	InputHandler(const InputHandler& other) = delete;
	InputHandler& operator= (const InputHandler& other) = delete;
	InputHandler(const InputHandler&& other) = delete;
	InputHandler& operator= (const InputHandler&& other) = delete;

	static std::map<int, int> keys;
	static std::map<int, int> mouseButtons;
	static std::pair<double, double> mousePosition;
};

