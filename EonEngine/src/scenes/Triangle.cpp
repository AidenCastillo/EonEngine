#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <imgui.h>

#include <iostream>
#include <string>
#include "../core/demoShader.h"
#include "../core/Renderer.h"
#include "../core/VertexBuffer.h"
#include "../core/IndexBuffer.h"
#include "../core/VertexArray.h"
#include "../core/VertexBufferLayout.h"
#include "../core/Texture.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "../controller/controller.h"
#include "Triangle.h"



using namespace std;




static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GLFW_TRUE);
}



void runScene(GLFWwindow* window) {
	// load shaders

	float vertices[] = {
		-50.0f, -50.0f,
		50.0f, -50.0f,
		50.0f, 50.0f,
		-50.0f, 50.0f
	};
	
	unsigned int indices[] = {
		0, 1, 2,
		2, 3, 0
	};

	VertexArray va;
	VertexBuffer vb(vertices, 4 * 2 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	IndexBuffer ib(indices, 6);

	glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 10.0f);

	Shader s;
	s.loadShaderProgramFromFile(RESOURCES_PATH "second.vertex", RESOURCES_PATH "second.fragment");
	s.bind();

	// create gui
	ImGui::CreateContext();
	ImGui_ImplOpenGL3_Init("#version 130");
	ImGui_ImplGlfw_InitForOpenGL(window, true);

	glm::vec3 translationA(0.0f, 0.0f, 0.0f);
	glm::vec3 translationB(0.0f, 0.0f, 0.0f);

	glm::vec3* translation = &translationA;

	Renderer renderer;
	Controller controller;

	{
		while (!glfwWindowShouldClose(window))
		{
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			controller.ProcessInput(window, translation);


			// render the triangle
			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);
				glm::mat4 mvp = proj * model;

				s.SetUniform4f("u_MVP", mvp);
				s.bind();
				renderer.Draw(va, ib, s);

			}
			// render gui
			{
				ImGui::SliderFloat3("Translation A", &translationA.x, 0.0f, 960.0f);
				ImGui::SliderFloat3("Translation B", &translationB.x, 0.0f, 960.0f);
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}
			
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}

	glfwTerminate();
}
