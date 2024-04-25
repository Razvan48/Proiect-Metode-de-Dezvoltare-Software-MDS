#pragma once

#include <vector>
#include <string>

#include "Texture.h"

class Flipbook
{
public:
	Flipbook();
	~Flipbook() = default;

	Flipbook(const Flipbook& other) = default;
	Flipbook& operator= (const Flipbook& other) = default;

	// TODO: move constructor

	inline void setFramesPerSecond(const float& framesPerSecond) { this->framesPerSecond = framesPerSecond; }
	inline void addFrame(const std::string& texture) { keyFrames.push_back(texture); }

	Texture2D& getTextureAtTime(double time) const;
	Texture2D& getTextureAtIndex(int index) const;
	int getNumFrames() const;

private:
	float framesPerSecond;
	std::vector<std::string> keyFrames;

	float getTotalDuration() const;
	int getKeyFrameIndexAtTime(double time) const;
};

