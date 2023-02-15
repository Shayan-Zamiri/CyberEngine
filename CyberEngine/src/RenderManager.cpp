/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "RenderManager.h"
#include "Camera.h"
#include "FileManager.h"
#include "GUIManager.h"
#include "Shader.h"
#include "Mesh.h"
#include "Model.h"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/gtc/matrix_transform.hpp"

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

		// Get version info
		mRendererName = glGetString(GL_RENDERER);
		mOpenGLVersion = glGetString(GL_VERSION);
		spdlog::info("Renderer: {}", mRendererName);
		spdlog::info("OpenGL version supported {}", mOpenGLVersion);

		// tell GL to only draw onto a pixel if the shape is closer to the viewer
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		// Don't draw back-face of triangles
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);

		mClearColor = glm::vec4{0.45f, 0.55f, 0.60f, 1.00f};

		// Shaders
		const std::string FragmentShader = FileManager::FileToString("../../../../Shaders/FragmentShader.glsl");
		const std::string VertexShader = FileManager::FileToString("../../../../Shaders/VertexShader.glsl");
		mShader = std::make_unique<Shader>(VertexShader, FragmentShader);
		mShader->Compile();
		mShader->Link();
		mShader->Bind();

		// Camera
		mCamera = std::make_unique<Camera>();

		// Model
		mModel = std::make_unique<Model>();
		mModel->LoadModel("../../../../Resources/backpack/backpack.obj");
		mModel->SetupMeshesTextures(*mShader);
	};

	void RenderManager::Render(float pDeltaTime)
	{
		OPTICK_EVENT("RenderManager::Render");
		mClearColor = gGUIManager.GetClearColor();
		//mCamera->SetPosition(gGUIManager.GetCameraPosition());
		//mCamera->SetRotation(gGUIManager.GetCameraPitch(), gGUIManager.GetCameraYaw());
		mCamera->Update(pDeltaTime);

		// Model Matrix
		static glm::mat4 ModelMatrix = translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -10.0));

		// Send our transformation to the currently bound shader
		mShader->SetUniformMat4f("u_ProjectionMatrix", mCamera->GetProjectionMatrix());
		mShader->SetUniformMat4f("u_ViewMatrix", mCamera->GetViewMatrix());
		mShader->SetUniformMat4f("u_ModelMatrix", ModelMatrix);

		// Rendering
		ImGui::Render();
		I32 Width, Height;
		glfwGetFramebufferSize(gGUIManager.GetGLFWWindow(), &Width, &Height);
		gGUIManager.SetDisplayWidth(Width);
		gGUIManager.SetDisplayHeight(Height);

		glViewport(0, 0, Width, Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
		mModel->Draw();

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(gGUIManager.GetGLFWWindow());
	}

	void RenderManager::ShutDown() { }
}
