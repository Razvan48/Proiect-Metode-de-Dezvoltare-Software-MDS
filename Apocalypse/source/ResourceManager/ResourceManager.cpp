#include "ResourceManager.h"

#include <iostream>
#include <sstream>
#include <fstream>

#include "stb_image.h"

// instantiate static variables
std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

Shader ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
	shaders[name] = loadShaderFromFile(vShaderFile, fShaderFile, gShaderFile);
	return shaders[name];
}

Shader& ResourceManager::getShader(std::string name)
{
	return shaders[name];
}

Texture2D ResourceManager::loadTexture(const char* file, bool alpha, std::string name)
{
	textures[name] = loadTextureFromFile(file, alpha);
	return textures[name];
}

Texture2D& ResourceManager::getTexture(std::string name)
{
	return textures[name];
}

void ResourceManager::clear()
{
	// delete all shaders
	for (auto iter : shaders)
		glDeleteProgram(iter.second.ID);
	// delete all textures
	for (auto iter : textures)
		glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile)
{
	// 1. retrieve the vertex/fragment source code from file path
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	try
	{
		// open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);

		std::stringstream vShaderStream, fShaderStream;

		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();

		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();

		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();

		if (gShaderFile)
		{
			std::ifstream geometryShaderFile(gShaderFile);
			std::stringstream gShaderStream;
			gShaderStream << geometryShaderFile.rdbuf();
			geometryShaderFile.close();
			geometryCode = gShaderStream.str();
		}
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER:: Failed to read shader files" << std::endl;
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	// 2. create shader object from source code
	Shader shader;
	shader.compile(vShaderCode, fShaderCode, gShaderFile ? gShaderCode : nullptr);
	return shader;
}

Texture2D ResourceManager::loadTextureFromFile(const char* file, bool alpha)
{
	// create texture object
	Texture2D texture;

	if (alpha)
	{
		texture.internalFormat = GL_RGBA;
		texture.imageFormat = GL_RGBA;
	}

	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	// generate texture
	texture.generate(width, height, data);

	// free image data
	stbi_image_free(data);
	return texture;
}

