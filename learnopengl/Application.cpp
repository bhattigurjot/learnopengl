#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "src/Shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Screen settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

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

	// glad: load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cerr << "Failed to initialize GLAD" << std::endl;
		return -1;
	}
	
	Shader ourShader("shaders/vShader.vs", "shaders/fShader.fs");

	// Vertex Data for a triangle
	float vertices[] = {
		// positions        // colors
		-0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f, // Left vertex
		 0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f, // Right vertex
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f, // Top vertex
	};

	// Vertex Array Object
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	// Vertex Buffer Object
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);
	// Copy vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// Set Vertex position Attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	// Set Vertex color Attributes pointers
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));
	glEnableVertexAttribArray(1);
	// Unbind VBO as glVertexAttribPointer registered VBO as vertex attribute's bound vertex
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	// Unbind VAO, so that other VAO calls don't modify this VAO
	glBindVertexArray(0);

	// Loop until the user closes the window
	while (!glfwWindowShouldClose(window))
	{
		// Process inputs 
		processInput(window);
		// Render here
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Activate program object; every shader and rendering call after uses this program
		ourShader.use();
		glBindVertexArray(VAO); // not required here, because of only single VAO
		glDrawArrays(GL_TRIANGLES, 0, 3);

		// Swap front and back buffers
		glfwSwapBuffers(window);
		// Poll for and process events
		glfwPollEvents();
	}

	// Delete allocated resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// Clear all previously allocated GLFW resources and terminate
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//	Setframebuffer callback function for resizing window 
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window)
{
	//	Process inputs in the window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}