#pragma once

#include "windowManager.h"

#include <iostream> //TODO: debug
#include <vector>
#include <string>
#include <map>

class AssetsManager
{
private:

	class TextureStructure
	{
	public:
		unsigned int id;
		int width;
		int height;
		int numChannels;

	public:
		TextureStructure(unsigned int id, int width, int height, int numChannels);

	};

	class AnimationStructure
	{
	public:
		std::vector<unsigned int> framesIds;

		double duration;
		double durationPerFrame;

	public:
		AnimationStructure(std::string name, size_t size, double duration);

	};

	AssetsManager();
	~AssetsManager();
	AssetsManager(const AssetsManager& other) = delete;
	AssetsManager& operator= (const AssetsManager& other) = delete;
	AssetsManager(const AssetsManager&& other) = delete;
	AssetsManager& operator= (const AssetsManager&& other) = delete;

private:

	std::map<std::string, AssetsManager::TextureStructure> textures;
	std::map<std::string, AssetsManager::AnimationStructure> animations;

public:
	static AssetsManager& get();
	void addTexture(const std::string& name, const std::string& address);
	void addAnimation(const std::string& name, const std::vector<std::string>& framesAddresses, double duration);
	unsigned int getTextureId(const std::string& name);
	const AssetsManager::AnimationStructure& getAnimation(const std::string& name);
};