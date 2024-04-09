#include "Flipbook.h"

#include <iostream> // TODO: delete
#include <math.h>

#include "ResourceManager.h"

Flipbook::Flipbook()
	: framesPerSecond(15.0f)
	, keyFrames()
{

}

int Flipbook::getNumFrames() const
{
	// TODO: cazul in care vrem sa avem un frameRun pt fiecare textura/sprite din flipbook
	return static_cast<int>(keyFrames.size());
}

float Flipbook::getTotalDuration() const
{
	if (framesPerSecond != 0.0f)
	{
		return getNumFrames() / framesPerSecond;
	}

	return 0.0f;
}

int Flipbook::getKeyFrameIndexAtTime(float time) const
{
	if (time < 0.0f)
	{
		return -1;
	}
	
	time = fmod(time, getTotalDuration());
	time *= framesPerSecond;

	return static_cast<int>(floor(time));
}

Texture2D& Flipbook::getTextureAtTime(float time) const
{
	const int keyFrameIndex = getKeyFrameIndexAtTime(time);
	return ResourceManager::getTexture(keyFrames[keyFrameIndex]);
}

