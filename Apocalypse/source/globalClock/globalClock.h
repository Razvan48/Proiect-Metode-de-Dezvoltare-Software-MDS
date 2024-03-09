#pragma once

#include "../windowManager/windowManager.h"

class GlobalClock
{
private:
	GlobalClock();
	~GlobalClock();
	GlobalClock(const GlobalClock& other) = delete;
	GlobalClock& operator= (const GlobalClock& other) = delete;
	GlobalClock(const GlobalClock&& other) = delete;
	GlobalClock& operator= (const GlobalClock&& other) = delete;

private:
	double previousTime;
	double currentTime;
	double deltaTime;

public:
	static GlobalClock& get();
	void updateTime();
	double getDeltaTime();
};
