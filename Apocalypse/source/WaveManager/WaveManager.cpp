#include "WaveManager.h"

WaveManager::WaveManager()
{

}

WaveManager& WaveManager::get()
{
	static WaveManager instance;
	return instance;
}

WaveManager::~WaveManager()
{

}

void WaveManager::update()
{
	// TODO:
}