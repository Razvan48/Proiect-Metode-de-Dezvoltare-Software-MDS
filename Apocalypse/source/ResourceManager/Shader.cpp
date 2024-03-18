#include "Shader.h"

#include <iostream>

Shader& Shader::use()
{
	glUseProgram(this->ID);
	return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource, const char* geometryShader)
{
	unsigned int sVertex, sFragment, sGeometry;

	// vertex Shader
	sVertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(sVertex, 1, &vertexSource, NULL);
	glCompileShader(sVertex);
	checkCompileErrors(sVertex, "VERTEX");

	// fragment Shader
	sFragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(sFragment, 1, &fragmentSource, NULL);
	glCompileShader(sFragment);
	checkCompileErrors(sFragment, "FRAGMENT");

	// geometry Shader
	if (geometryShader)
	{
		sGeometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(sGeometry, 1, &geometryShader, NULL);
		glCompileShader(sGeometry);
		checkCompileErrors(sGeometry, "GEOMETRY");
	}

	// shader program
	this->ID = glCreateProgram();
	glAttachShader(this->ID, sVertex);
	glAttachShader(this->ID, sFragment);
	if (geometryShader)
		glAttachShader(this->ID, sGeometry);

	glLinkProgram(this->ID);
	checkCompileErrors(this->ID, "PROGRAM");

	// delete the shaders
	glDeleteShader(sVertex);
	glDeleteShader(sFragment);
	if (geometryShader)
		glDeleteShader(sGeometry);
}

void Shader::setFloat(const char* name, float value, bool useShader)
{
	if (useShader)
		this->use();
	glUniform1f(glGetUniformLocation(this->ID, name), value);
}

void Shader::setInteger(const char* name, int value, bool useShader)
{
	if (useShader)
		this->use();
	glUniform1i(glGetUniformLocation(this->ID, name), value);
}

void Shader::setVector2f(const char* name, const glm::vec2& value, bool useShader)
{
	if (useShader)
		this->use();
	glUniform2f(glGetUniformLocation(this->ID, name), value.x, value.y);
}

void Shader::setVector3f(const char* name, const glm::vec3& value, bool useShader)
{
	if (useShader)
		this->use();
	glUniform3f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z);
}

void Shader::setVector4f(const char* name, const glm::vec4& value, bool useShader)
{
	if (useShader)
		this->use();
	glUniform4f(glGetUniformLocation(this->ID, name), value.x, value.y, value.z, value.w);
}

void Shader::setMatrix4(const char* name, const glm::mat4& value, bool useShader)
{
	if (useShader)
		this->use();
	glUniformMatrix4fv(glGetUniformLocation(this->ID, name), 1, false, glm::value_ptr(value));
}

void Shader::checkCompileErrors(unsigned int object, std::string type)
{
	int success;
	char infoLog[1024];

	if (type != "PROGRAM")
	{
		glGetShaderiv(object, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::SHADER:: Compile-time error: Type: " << type << '\n' << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(object, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(object, 1024, NULL, infoLog);
			std::cout << "| ERROR::PROGRAM:: Link-time error: Type: " << type << '\n' << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}

