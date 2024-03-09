#include "globalClock.h"

GlobalClock::GlobalClock() :
	previousTime(0.0), currentTime(0.0), deltaTime(0.0)
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

double GlobalClock::getDeltaTime()
{
	return this->deltaTime;
}