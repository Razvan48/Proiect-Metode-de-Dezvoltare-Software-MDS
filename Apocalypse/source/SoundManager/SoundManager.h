#pragma once

#include <fmod.hpp>

class SoundManager
{
public:
	static FMOD::System* get();

private:
	SoundManager();
	~SoundManager();

	SoundManager(const SoundManager& other) = delete;
	SoundManager& operator= (const SoundManager& other) = delete;
	SoundManager(const SoundManager&& other) = delete;
	SoundManager& operator= (const SoundManager&& other) = delete;

	static FMOD::System* fmodSystem;
};

