#pragma once

#include <glad/glad.h>

#include <map>
#include <string>

#include "texture.h"
#include "shader.h"

class ResourceManager
{
public:
	// resource storage
	static std::map<std::string, Shader> shaders;
	static std::map<std::string, Texture2D> textures;

	// load and generate a shader program from files: vertex, fragment, geometry
	static void loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// retrieve a stored shader
	static Shader& getShader(const std::string& name);

	// load and generate a texture from file
	static void loadTexture(const char* file, const bool& alpha, const std::string& name);

	// retrieve a stored texture
	static Texture2D& getTexture(const std::string& name);

	// de-allocate all resources
	static void clear();

private:
	ResourceManager() = default;
	~ResourceManager() = default;

	ResourceManager(const ResourceManager& other) = delete;
	ResourceManager& operator= (const ResourceManager& other) = delete;
	ResourceManager(const ResourceManager&& other) = delete;
	ResourceManager& operator= (const ResourceManager&& other) = delete;
};

