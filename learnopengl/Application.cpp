#include <GLFW/glfw3.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Screen settings
const unsigned SCREEN_WIDTH = 800;
const unsigned SCREEN_HEIGHT = 600;

int main(void)
{
	// Initialize the library
	if (!glfwInit())
		return -1;
	else 
	{
		// Configure GLFW if it initializes successfully
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	}

	// Create a windowed mode window and its OpenGL context
	GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Opengl Window", NULL, NULL);
	if (!window)
	{
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Make the window's context current
	glfwMakeContextCurrent(window);
	// Register setframebuffer callback function for resizing window
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Process inputs 
		processInput(window);
		// Render here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();
	}

	// Clear all previously allocated GLFW resources and terminate
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	/* 
		Setframebuffer callback function for resizing window 
	*/
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	/* 
		Process inputs in the window
	*/
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}