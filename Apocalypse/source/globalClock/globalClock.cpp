#include "globalClock.h"

#include "../windowManager/windowManager.h"

GlobalClock::GlobalClock() 
	: previousTime(0.0), currentTime(0.0), deltaTime(0.0)
{
	WindowManager::get();
}

GlobalClock::~GlobalClock()
{

}

GlobalClock& GlobalClock::get()
{
	static GlobalClock instance;

	return instance;
}

void GlobalClock::updateTime()
{
	this->currentTime = glfwGetTime();
	this->deltaTime = this->currentTime - this->previousTime;
	this->previousTime = this->currentTime;
}

