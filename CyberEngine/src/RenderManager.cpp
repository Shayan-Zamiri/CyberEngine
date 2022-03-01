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
		{
			spdlog::error("Error: could not start GLFW");
			return;
		}

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello World", nullptr, nullptr);
		if (!window)
		{
			spdlog::error("Error: could not open window with GLFW3");
			glfwTerminate();
			return;
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			spdlog::error("Error: Failed to initialize GLAD");
			return;
		}

		// get version info
		const U8* Renderer = glGetString(GL_RENDERER);
		const U8* Version = glGetString(GL_VERSION);
		spdlog::info("Renderer: {}", Renderer);
		spdlog::info("OpenGL version supported {}", Version);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST); // enable depth-testing
		glDepthFunc(GL_LESS);    // depth-testing interprets a smaller value as "closer"

		// Triangle vertices
		constexpr float Vertices[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};

		// Vertex Buffer Object
		U32 VBO = 0;
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices,GL_STATIC_DRAW);

		// Vertex Attribute Object
		U32 VAO = 0;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

		// Vertex Shader
		const char* VertexShader =
			"#version 400\n"
			"in vec3 vp;"
			"void main () {"
			" gl_Position = vec4 (vp, 1.0);"
			"}";

		// Fragment Shader
		const char* FragmentShader =
			"#version 400\n"
			"out vec4 frag_colour;"
			"void main () {"
			" frag_colour = vec4 (0.2, 0.3, 0.6, 1.0);"
			"}";

		const U32 VS = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(VS, 1, &VertexShader, nullptr);
		glCompileShader(VS);

		const U32 FS = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(FS, 1, &FragmentShader, nullptr);
		glCompileShader(FS);

		const U32 ShaderProgram = glCreateProgram();
		glAttachShader(ShaderProgram, FS);
		glAttachShader(ShaderProgram, VS);
		glLinkProgram(ShaderProgram);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			// wipe the drawing surface clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glUseProgram(ShaderProgram);
			glBindVertexArray(VAO);

			// draw points 0-3 from the currently bound VAO with current in-use shader
			glDrawArrays(GL_TRIANGLES, 0, 3);

			// update other events like input handling
			glfwPollEvents();

			// put the stuff we've been drawing onto the display
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}

	void RenderManager::ShutDown() { }
}
