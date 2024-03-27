#include "WindowManager.h"

#include <iostream>

WindowManager::WindowManager() 
	: WINDOW_WIDTH(1024), WINDOW_HEIGHT(800), WINDOW_TITLE("Apocalypse")
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

	// Successfully created GLFW Window
	std::cout << "Created GLFW Window" << std::endl;

	// Set GLFW context
	glfwMakeContextCurrent(window);

	// Load OpenGL functions, gladLoadGL returns the loaded version, 0 on error
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return;
	}

	// Successfully loaded GLAD
	std::cout << "Loaded GLAD" << std::endl;

	// TODO
	// Set the required callback functions
	// glfwSetKeyCallback(window, key_callback);
	// glfwSetMouseButtonCallback(window, mouse_button_callback);

	// TODO
	// OpenGL configuration
	//glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

	//glEnable(GL_BLEND);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

WindowManager::~WindowManager()
{
	// Destroy window
	glfwDestroyWindow(this->window);

	// Terminates GLFW, clearing any resources allocated by GLFW
	glfwTerminate();
}

WindowManager& WindowManager::get()
{
	static WindowManager instance;
	return instance;
}

