/*
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
*/

//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"

#include "windowManager/windowManager.h"
#include <iostream>

//void processInput(GLFWwindow* window);

// window settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 900;

int main()
{

	/*

	///////////////////////////////////////////////////

	// Load image
	int width, height, channels;
	unsigned char *img = stbi_load("textures/OpenGL-test.png", &width, &height, &channels, 0);
	
	if (img == nullptr)
	{
		std::cout << "Error in loading the image\n";
	}
	else
	{
		std::cout << "Loaded image with a width of " << width << ", a height of " << height << " and " << channels << " channels\n";
		stbi_image_free(img);
	}

	// Loop
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Render
		glClearColor(0.733f, 0.024f, 0.259f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap the screen buffers
		glfwSwapBuffers(window);

		// Check if any events have been activated (key pressed, mouse moved etc.) and call corresponding response functions
		glfwPollEvents();
	}

	// Terminates GLFW, clearing any resources allocated by GLFW
	glfwTerminate();

	*/
	return 0;
}

/*
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}
*/

