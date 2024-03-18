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
	static Shader loadShader(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile, std::string name);

	// retrieve a stored shader
	static Shader& getShader(std::string name);

	// load and generate a texture from file
	static Texture2D loadTexture(const char* file, bool alpha, std::string name);

	// retrieve a stored texture
	static Texture2D& getTexture(std::string name);

	// de-allocate all resources
	static void clear();

private:
	ResourceManager() {  }

	// load and generate a shader from file
	static Shader loadShaderFromFile(const char* vShaderFile, const char* fShaderFile, const char* gShaderFile = nullptr);

	// load a single texture from file
	static Texture2D loadTextureFromFile(const char* file, bool alpha);
};

