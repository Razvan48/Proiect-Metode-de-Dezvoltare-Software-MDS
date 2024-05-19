#pragma once

class WaveManager
{
private:

	WaveManager();
	~WaveManager();
	WaveManager(const WaveManager& other) = delete;
	WaveManager& operator= (const WaveManager& other) = delete;
	WaveManager(const WaveManager&& other) = delete;
	WaveManager& operator= (const WaveManager&& other) = delete;

public:

	static WaveManager& get();

	void update(); // TODO:
};