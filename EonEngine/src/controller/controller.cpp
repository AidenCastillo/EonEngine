#include "controller.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


Controller::Controller()
	: m_Window(nullptr)
{
}

Controller::~Controller()
{

}

void Controller::ProcessInput(GLFWwindow* m_Window)
{
	if (glfwGetKey(m_Window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_Window, true);

	if (glfwGetKey(m_Window, GLFW_KEY_W) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(m_Window, GLFW_KEY_F) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (glfwGetKey(m_Window, GLFW_KEY_P) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	// if arrow keys are pressed, move the camera
	if (glfwGetKey(m_Window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		std::cout << "UP" << std::endl;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		std::cout << "DOWN" << std::endl;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		std::cout << "LEFT" << std::endl;
	}
	if (glfwGetKey(m_Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		std::cout << "RIGHT" << std::endl;
	}

}