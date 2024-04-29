#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Controller
{
private:
	GLFWwindow* m_Window;

public:
	Controller();
	~Controller();

	void ProcessInput(GLFWwindow* m_Window);
};