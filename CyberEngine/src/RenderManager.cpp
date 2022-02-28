#include "CEPCH.h"
#include "RenderManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	RenderManager::RenderManager() {}

	RenderManager::~RenderManager() {}

	// FUNCTIONS

	void RenderManager::StartUp() { }

	void RenderManager::Render()
	{
		/* Initialize the library */
		if (!glfwInit())
			return;

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(640, 480, "Hello World", nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cout << "Failed to initialize GLAD" << std::endl;
			return;
		}

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);

			/* Swap front and back buffers */
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
		}

		glfwTerminate();

		return;
	}

	void RenderManager::ShutDown() { }
}
