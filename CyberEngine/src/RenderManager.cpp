#include "CEPCH.h"
#include "RenderManager.h"
#include "GUIManager.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
#include "glm/gtc/matrix_transform.hpp"
#include "FileManager.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	RenderManager::RenderManager() {}

	RenderManager::~RenderManager() {}

	// FUNCTIONS

	void RenderManager::StartUp()
	{
		// Initialize GLAD
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			spdlog::error("Error: Failed to initialize GLAD");
			return;
		}

		glHint(GL_FRAGMENT_SHADER_DERIVATIVE_HINT, GL_NICEST);
		glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
		glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
		glHint(GL_TEXTURE_COMPRESSION_HINT, GL_NICEST);

		// Setup Platform/Renderer backend
		mGLSLVersion = "#version 460";
		ImGui_ImplGlfw_InitForOpenGL(gGUIManager.GetGLFWWindow(), true);
		ImGui_ImplOpenGL3_Init(mGLSLVersion.c_str());

		// get version info
		mRendererName = glGetString(GL_RENDERER);
		mOpenGLVersion = glGetString(GL_VERSION);
		spdlog::info("Renderer: {}", mRendererName);
		spdlog::info("OpenGL version supported {}", mOpenGLVersion);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		mClearColor = glm::vec4{0.45f, 0.55f, 0.60f, 1.00f};
		mObjectColor = glm::vec4{0.2f, 0.7f, 0.3f, 1.0f};
		mWorld = glm::vec3{4.0f, 3.0f, 3.0f};
		mOrigin = glm::vec3{0.0f, 0.0f, 0.0f};

		// Shaders
		const std::string FragmentShader = FileManager::FileToString("../../../../Shaders/FragmentShader.glsl");
		const std::string VertexShader = FileManager::FileToString("../../../../Shaders/VertexShader.glsl");
		mShader = std::make_unique<Shader>(VertexShader, FragmentShader);
		mShader->Compile();
		mShader->Link();
		mShader->Bind();
	}

	void RenderManager::Render()
	{
		// Projection Matrix
		const glm::mat4 Projection = glm::perspective(glm::radians(60.0f), 1920.0f / 1080.0f, 0.1f, 100.0f);

		// Camera Matrix
		const glm::mat4 View = glm::lookAt(
			mWorld,            // Camera is at (4,3,3), in World Space
			mOrigin,           // and looks at the origin
			glm::vec3(0, 1, 0) // Head is up (set to 0,-1,0 to look upside-down)
		);

		// Model Matrix : an identity matrix (model will be at the origin)
		const glm::mat4 Model = glm::mat4(1.0f);

		// Model View Projection Matrix
		const glm::mat4 MVPMatrix = Projection * View * Model;

		// Send our transformation to the currently bound shader, in the "MVP" uniform
		mShader->SetUniformMat4f("u_MVP", MVPMatrix);
		mShader->SetUniform4f("u_Color", mObjectColor.x, mObjectColor.y, mObjectColor.z, mObjectColor.w);

		// Triangle vertices
		constexpr float Vertices[] = {-0.5, 0.5f, 0.0f, 0.5f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
		constexpr U32 Indices[] = {0, 1, 2, 2, 3, 0};

		// Vertex Buffer Object
		VertexBuffer VBO{};
		VBO.Bind();
		VBO.FillBuffer(Vertices, sizeof(Vertices));
		VBO.AddVBElement<float>(3);

		// Vertex Attribute Object
		VertexArray VAO{};
		VAO.Bind();
		VAO.AddVBO(VBO);

		// Index Buffer
		IndexBuffer IB{};
		IB.FillBuffer(Indices, 6);
		IB.Bind();

		// Rendering
		ImGui::Render();
		I32 Width, Height;
		glfwGetFramebufferSize(gGUIManager.GetGLFWWindow(), &Width, &Height);
		gGUIManager.SetDisplayWidth(Width);
		gGUIManager.SetDisplayHeight(Height);

		glViewport(0, 0, Width, Height);
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawElements(GL_TRIANGLES, IB.GetCount(), GL_UNSIGNED_INT, nullptr);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(gGUIManager.GetGLFWWindow());
	}

	void RenderManager::ShutDown() { }
}
