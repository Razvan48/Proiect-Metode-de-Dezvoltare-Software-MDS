#include "assetsManager.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "../windowManager/windowManager.h"

#include <iostream> // TODO: debug

AssetsManager::TextureStructure::TextureStructure(unsigned int id = 0, int width = 0, int height = 0, int numChannels = 0) :
	id(id), width(width), height(height), numChannels(numChannels)
{

}

AssetsManager::AnimationStructure::AnimationStructure(std::string name = "", size_t size = 0, double duration = 0.0) :
	duration(duration), durationPerFrame(duration / size)
{
	for (size_t i = 0; i < size; ++i)
	{
		this->framesIds.emplace_back(AssetsManager::get().getTextureId(name + std::to_string(i)));
	}
}

AssetsManager& AssetsManager::get()
{
	// Ne asiguram ca WindowManager exista inainte sa instantiem AssetsManager (deoarece WindowManager instantiaza tot OpenGL-ul)
	WindowManager::get();

	static AssetsManager instance;

	return instance;
}

void AssetsManager::addTexture(const std::string& name, const std::string& address)
{
	if (this->textures.find(name) == this->textures.end())
	{
		AssetsManager::TextureStructure texture;

		texture.id = 0; //

		glGenTextures(1, &texture.id);
		glBindTexture(GL_TEXTURE_2D, texture.id);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		// Load image
		unsigned char* data = stbi_load(address.c_str(), &texture.width, &texture.height, &texture.numChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.width, texture.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			this->textures.insert({ name, texture });
		}
		else
		{
			std::cout << "Error AssetsManager: could not add the texture!" << '\n';
			stbi_image_free(data);
		}

		// stbi_image_free(data);
	}
	else
	{
		// TODO: conventie formatare mesaje eroare
		// std::cout << "Error AssetsManager: texture with same name already in memory!" << '\n';
	}
}

void AssetsManager::addAnimation(const std::string& name, const std::vector<std::string>& framesAddresses, double duration)
{
	if (this->animations.find(name) == this->animations.end())
	{
		for (size_t i = 0; i < framesAddresses.size(); ++i)
			this->addTexture(name + std::to_string(i), framesAddresses[i]);

		AssetsManager::AnimationStructure animation(name, framesAddresses.size(), duration);

		this->animations.insert({ name, animation });
	}
	else
	{
		// TODO: conventie formatare mesaje eroare
		// std::cout << "Error AssetsManager: animation with same name already in memory!" << '\n';
	}
}

unsigned int AssetsManager::getTextureId(const std::string& name)
{
	if (this->textures.find(name) == this->textures.end())
	{
		// TODO: conventie formatare mesaje eroare
		std::cout << "Error AssetsManager: could not find the texture!" << '\n';

		return 0;
	}

	return this->textures[name].id;
}

const AssetsManager::AnimationStructure& AssetsManager::getAnimation(const std::string& name)
{
	if (this->animations.find(name) == this->animations.end())
	{
		// TODO: conventie formatare mesaje eroare
		std::cout << "Error AssetsManager: could not find the animation!" << '\n';

		return AnimationStructure();
	}

	return this->animations[name];
}

