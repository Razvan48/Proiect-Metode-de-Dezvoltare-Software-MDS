#include "SoundManager.h"

#include <iostream> // TODO: delete

// instantiate static variables
FMOD::System* SoundManager::fmodSystem = nullptr;

SoundManager::SoundManager()
{
	// Initialize Sound System
	if (FMOD::System_Create(&fmodSystem) != FMOD_OK)
	{
		// TODO: throw + unit test
		std::cout << "ERROR : SOUND SYSTEM NOT CREATED!" << std::endl;
	}
	else
	{
		std::cout << "SOUND SYSTEM CREATED!" << std::endl;
		fmodSystem->init(32, FMOD_INIT_NORMAL, NULL);
	}
}

SoundManager::~SoundManager()
{
	fmodSystem->close();
	fmodSystem->release();
}

FMOD::System* SoundManager::get()
{
	static SoundManager instance;
	return fmodSystem;
}

