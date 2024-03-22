#include "ResourceManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "stb_image.h"

// instantiate static variables
std::map<std::string, Texture2D> ResourceManager::textures;
std::map<std::string, Shader> ResourceManager::shaders;

void ResourceManager::loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name)
{
	shaders[name] = Shader();

	// retrieve the vertex/fragment/geometry source code from file path
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;

	// open files
	std::ifstream vertexShaderFile(vShaderFile);
	if (vertexShaderFile.fail())
	{
		throw std::runtime_error("Cannot open file: " + std::string(vShaderFile));
	}

	std::ifstream fragmentShaderFile(fShaderFile);
	if (fragmentShaderFile.fail())
	{
		throw std::runtime_error("Cannot open file: " + std::string(fShaderFile));
	}

	// read file's buffer contents into streams
	std::stringstream vShaderStream, fShaderStream;

	vShaderStream << vertexShaderFile.rdbuf();
	fShaderStream << fragmentShaderFile.rdbuf();

	// close file handlers
	vertexShaderFile.close();
	fragmentShaderFile.close();

	// convert stream into string
	vertexCode = vShaderStream.str();
	fragmentCode = fShaderStream.str();

	// optional parameter
	if (gShaderFile)
	{
		std::ifstream geometryShaderFile(gShaderFile);
		if (geometryShaderFile.fail())
		{
			throw std::runtime_error("Cannot open file: " + std::string(gShaderFile));
		}

		std::stringstream gShaderStream;
		gShaderStream << geometryShaderFile.rdbuf();
		geometryShaderFile.close();
		geometryCode = gShaderStream.str();
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	const char* gShaderCode = geometryCode.c_str();

	// create shader object from source code
	shaders[name].compile(vShaderCode, fShaderCode, gShaderFile ? gShaderCode : nullptr);
}

Shader& ResourceManager::getShader(const std::string& name)
{
	if (shaders.find(name) == shaders.end())
	{
		// TODO: conventie formatare mesaje eroare
		std::cout << "Error ResourceManager: could not find the shader!\n";
	}

	return shaders[name];
}

void ResourceManager::loadTexture(const char* file, const bool& alpha, const std::string& name)
{
	// create texture object
	textures[name] = Texture2D();

	if (alpha)
	{
		textures[name].internalFormat = GL_RGBA;
		textures[name].imageFormat = GL_RGBA;
	}

	// load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);

	if (data == nullptr)
	{
		throw std::runtime_error("Cannot open file: " + std::string(file));
	}

	// generate texture
	textures[name].generate(width, height, data);

	// free image data
	stbi_image_free(data);
}

Texture2D& ResourceManager::getTexture(const std::string& name)
{
	if (textures.find(name) == textures.end())
	{
		// TODO: conventie formatare mesaje eroare
		std::cout << "Error ResourceManager: could not find the texture!\n";
	}

	return textures[name];
}

void ResourceManager::clear()
{
	// delete all shaders
	for (const auto& it : shaders)
	{
		glDeleteProgram(it.second.ID);
	}

	// delete all textures
	for (const auto& it : textures)
	{
		glDeleteTextures(1, &it.second.ID);
	}
}

// TODO: load on demand 

