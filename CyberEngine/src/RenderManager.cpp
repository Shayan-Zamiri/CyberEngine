#include "CEPCH.h"
#include "RenderManager.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"

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

		glfwWindowHint(GLFW_SAMPLES, 16);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		/* Create a windowed mode window and its OpenGL context */
		GLFWwindow* window = glfwCreateWindow(1920, 1080, "Hello World", nullptr, nullptr);
		if (!window)
		{
			spdlog::error("Error: could not open window with GLFW3");
			glfwTerminate();
			return;
		}

		// Make the window's context current
		glfwMakeContextCurrent(window);

		// Ensure we can capture the escape key being pressed below
		glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

		// Hide the mouse and enable unlimited mouvement
		//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		// Set the mouse at the center of the screen
		glfwPollEvents();
		glfwSetCursorPos(window, 1920.0f / 2, 1080.0f / 2);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			spdlog::error("Error: Failed to initialize GLAD");
			return;
		}

		glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);

		// get version info
		const U8* Renderer = glGetString(GL_RENDERER);
		const U8* Version = glGetString(GL_VERSION);
		spdlog::info("Renderer: {}", Renderer);
		spdlog::info("OpenGL version supported {}", Version);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Triangle vertices
		constexpr float Vertices[] = {-0.5, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
		constexpr U32 Indices[] = {0, 1, 2, 2, 3, 0};

		// Vertex Buffer Object
		VertexBuffer VBO{Vertices, sizeof(Vertices)};
		VBO.AddVBElement<float>(3);
		VBO.Bind();

		// Vertex Attribute Object
		VertexArray VAO;
		VAO.Bind();
		VAO.AddBuffer(VBO);

		// Index Buffer
		IndexBuffer IB{Indices, 6};
		IB.Bind();

		// Projection Matrix
		glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		// Camera Matrix
		glm::mat4 View = glm::lookAt(
			glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
			glm::vec3(0, 0, 0), // and looks at the origin
			glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);

		// Model Matrix : an identity matrix (model will be at the origin)
		glm::mat4 Model = glm::mat4(1.0f);

		// Model View Projection Matrix
		glm::mat4 mvp = Projection * View * Model;

		// Vertex Shader
		const char* VertexShader =
			"#version 400\n"
			"layout(location = 0)"
			"in vec3 VP;"
			"uniform mat4 MVP;"
			"void main()"
			"{"
			"	gl_Position = MVP * vec4(VP, 1);"
			"}";

		// Fragment Shader
		const char* FragmentShader =
			"#version 400\n"
			"out vec4 frag_color;"
			"void main () {"
			" frag_color = vec4 (0.2, 0.3, 0.6, 1.0);"
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
		glUseProgram(ShaderProgram);

		// Get a handle for our "MVP" uniform
		// Only during the initialisation
		GLuint MatrixID = glGetUniformLocation(ShaderProgram, "MVP");

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &mvp[0][0]);

		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			// wipe the drawing surface clear
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			glDrawElements(GL_TRIANGLES, IB.GetCount(), GL_UNSIGNED_INT, nullptr);

			// update other events like input handling
			glfwPollEvents();

			// put the stuff we've been drawing onto the display
			glfwSwapBuffers(window);
		}

		glfwTerminate();
	}

	void RenderManager::ShutDown() { }
}
