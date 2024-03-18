#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

class WindowManager
{
private:
	WindowManager();
	~WindowManager();
	WindowManager(const WindowManager& other) = delete;
	WindowManager& operator= (const WindowManager& other) = delete;
	WindowManager(const WindowManager&& other) = delete;
	WindowManager& operator= (const WindowManager&& other) = delete;

private:
	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;
	std::string windowTitle;
	GLFWwindow* window;

	const char* vertexShaderSource;
	const char* fragmentShaderSource;
	unsigned int vao;
	unsigned int vbo;
	unsigned int vertexShader;
	unsigned int fragmentShader;
	unsigned int shaderProgram;

	int orthoPath;
	int texturePath;
	glm::mat4 ortho;

public:
	static WindowManager& get();
	inline int getWindowWidth() { return this->WINDOW_WIDTH; }
	inline int getWindowHeight() { return this->WINDOW_HEIGHT; }
	inline GLFWwindow* getWindow() { return this->window; }
};

