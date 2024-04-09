#pragma once

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

	inline double getDeltaTime() { return this->deltaTime; }
	inline double getCurrentTime() { return this->currentTime; }
};

