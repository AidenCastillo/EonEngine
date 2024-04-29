// EonEngine.cpp : Defines the entry point for the application.
//

#include "EonEngine.h"
#include "controller/controller.h"
#include "debug/Debug.h"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image/stb_image.h>
#include <imgui.h>

#include "core/Texture.h"
#include "core/Shader.h"
#include "core/VertexBuffer.h"
#include "core/IndexBuffer.h"
#include "core/VertexArray.h"
#include "core/VertexBufferLayout.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "core/Renderer.h"


using namespace std;



int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(960, 540, "EonEngine", NULL, NULL);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	/* Enable debug output */
	glDebugMessageCallback(glDebugOutput, nullptr);

	glEnable(GL_DEPTH_TEST);

	
	{

		float positions[] = {
				 -50.0f, -50.0f, 0.0f, 0.0f, // 0
				 50.0f, -50.0f, 1.0f, 0.0f, // 1
				 50.0f, 50.0f, 1.0f, 1.0f, // 2
				 -50.0f, 50.0f, 0.0f, 1.0f // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_BLEND));

		VertexArray va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);
		layout.Push<float>(2);
		va.AddBuffer(vb, layout);

		IndexBuffer ib(indices, 6);

		// Create a projection matrix
		// First 4 arguments are the bounds of the frustum
		// Last 2 arguments are the near and far planes
		// The near and far planes are the distance from the camera to the near and far planes
		// Anything outside of the frustum will not be rendered
		// Anything between the near and far planes will be rendered
		glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		Shader shader("E:/amc-m/Documents/code/Graphics/EonEngine/EonEngine/res/shaders/main");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture texture("E:/amc-m/Documents/code/Graphics/EonEngine/EonEngine/res/textures/ChernoLogo.png");
		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);

		va.UnBind();
		vb.UnBind();
		ib.UnBind();
		shader.Unbind();


		Renderer renderer;

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 130");
		ImGui::StyleColorsDark();

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			}

			{
				glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200, 200, 0));
				glm::mat4 mvp = proj * view * model;
				shader.SetUniformMat4f("u_MVP", mvp);
				shader.Bind();

				renderer.Draw(va, ib, shader);
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}
	}

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();

	glfwTerminate();

	return 0;
}
