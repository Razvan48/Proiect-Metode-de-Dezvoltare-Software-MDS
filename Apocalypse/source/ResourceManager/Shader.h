#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class Shader
{
public:
	// constructor
	Shader() = default;

	// state
	unsigned int ID;

	// sets the current shader as active
	Shader& use();

	// compile the shader from given source code
	void compile(const char* vertexSource, const char* fragmentSource, const char* geometryShader = nullptr);

	// utility functions
	void setFloat(const char* name, float value, bool useShader = false);
	void setInteger(const char* name, int value, bool useShader = false);
	void setVector2f(const char* name, const glm::vec2 &value, bool useShader = false);
	void setVector3f(const char* name, const glm::vec3 &value, bool useShader = false);
	void setVector4f(const char* name, const glm::vec4 &value, bool useShader = false);
	void setMatrix4(const char* name, const glm::mat4 &value, bool useShader = false);

private:
	// checks if compilation or linking failed and print errors
	void checkCompileErrors(unsigned int object, std::string type);
};

