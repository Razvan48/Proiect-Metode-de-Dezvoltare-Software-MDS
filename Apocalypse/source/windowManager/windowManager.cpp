#include "windowManager.h"

#include <iostream>

WindowManager::WindowManager() 
	: WINDOW_WIDTH(1024), WINDOW_HEIGHT(800), windowTitle("Apocalypse")
	, vertexShaderSource
		(
			"#version 330 core \n"
			"\n"
			"layout (location = 0) in vec2 vertexPosition; \n"
			"layout (location = 1) in vec2 texturePosition; \n"
			"uniform mat4 ortho; \n"
			"out vec2 passedTexturePosition; \n"
			"\n"
			"void main() \n"
			"{ \n"
			"\n"
			"   passedTexturePosition = texturePosition; \n"
			"   gl_Position = ortho * vec4(vertexPosition.x, vertexPosition.y, 0.0, 1.0); \n"
			"\n"
			"} \n"
			"\0"
		)
	, fragmentShaderSource
		(
			"#version 330 core \n"
			"\n"
			"in vec2 passedTexturePosition; \n"
			"out vec4 fragmentColour; \n"
			"uniform sampler2D texture0; \n"
			"\n"
			"void main() \n"
			"{ \n"
			"\n"
			"   vec4 textureColour = texture(texture0, passedTexturePosition); \n"
			"	if (textureColour.rgb == vec3(0.0, 0.0, 0.0)) \n"
			"	{ \n"
			"		discard; \n"
			"	} \n"
			"	fragmentColour = textureColour; \n"
			"\n"
			"} \n"
			"\0"
		)
{
	// Init GLFW
	glfwInit();

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // TODO: GL_TRUE?

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(this->WINDOW_WIDTH, this->WINDOW_HEIGHT, "Apocalypse", NULL, NULL);
	// glfwGetPrimaryMonitor(); // TODO
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return;
	}

	// Set GLFW context
	glfwMakeContextCurrent(window);

	// Set the required callback functions
	// TODO
	// glfwSetKeyCallback(window, key_callback);
	// glfwSetMouseButtonCallback(window, mouse_button_callback);

	// Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize OpenGL context" << std::endl;
		return;
	}

	// Successfully loaded OpenGL
	std::cout << "Loaded OpenGL " << std::endl;

	// TODO: de revazut daca e ok

	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &this->vertexShaderSource, NULL);
	glCompileShader(this->vertexShader);

	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &this->fragmentShaderSource, NULL);
	glCompileShader(this->fragmentShader);

	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, this->vertexShader);
	glAttachShader(this->shaderProgram, this->fragmentShader);
	glLinkProgram(this->shaderProgram);

	// glValidateProgram(this->shaderProgram);

	glDeleteShader(this->fragmentShader);
	glDeleteShader(this->vertexShader);

	glUseProgram(this->shaderProgram);

	this->orthoPath = glGetUniformLocation(this->shaderProgram, "ortho");
	this->ortho = glm::ortho(-0.5 * this->WINDOW_WIDTH, 0.5 * this->WINDOW_WIDTH, -0.5 * this->WINDOW_HEIGHT, 0.5 * this->WINDOW_HEIGHT);
	// this->ortho = glm::ortho(0.0, 1.0 * this->WINDOW_WIDTH, 0.0, 1.0 * this->WINDOW_HEIGHT);
	glUniformMatrix4fv(this->orthoPath, 1, GL_FALSE, glm::value_ptr(this->ortho));

	this->texturePath = glGetUniformLocation(this->shaderProgram, "texture0");
	glUniform1i(this->texturePath, 0);
	glActiveTexture(GL_TEXTURE0);

	glGenVertexArrays(1, &this->vao);
	glGenBuffers(1, &this->vbo);

	glBindVertexArray(this->vao);
	glBindBuffer(GL_ARRAY_BUFFER, this->vbo);

	glVertexAttribPointer(0, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_DOUBLE, GL_FALSE, 4 * sizeof(double), (void*)(2 * sizeof(double)));
	glEnableVertexAttribArray(1);
}

WindowManager::~WindowManager()
{
	glDeleteBuffers(1, &this->vbo);
	glDeleteVertexArrays(1, &this->vao);

	glDeleteProgram(this->shaderProgram);

	glfwDestroyWindow(this->window);

	// Terminates GLFW, clearing any resources allocated by GLFW
	glfwTerminate();
}

WindowManager& WindowManager::get()
{
	static WindowManager instance;

	return instance;
}

