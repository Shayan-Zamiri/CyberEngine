/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "RenderManager.h"
#include "Camera.h"
#include "GUIManager.h"
#include "Shader.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "FileManager.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"
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
		mObjectColor = glm::vec4{0.2f, 0.7f, 0.3f, 1.0f};

		// Shaders
		const std::string FragmentShader = FileManager::FileToString("../../../../Shaders/FragmentShader.glsl");
		const std::string VertexShader = FileManager::FileToString("../../../../Shaders/VertexShader.glsl");
		mShader = std::make_unique<Shader>(VertexShader, FragmentShader);
		mShader->Compile();
		mShader->Link();
		mShader->Bind();

		// Camera
		mCamera = std::make_unique<Camera>();

		constexpr GLfloat Vertices[] = {
			// front
			-1.0
		  , -1.0
		  , 1.0
		  , 1.0
		  , -1.0
		  , 1.0
		  , 1.0
		  , 1.0
		  , 1.0
		  , -1.0
		  , 1.0
		  , 1.0
		   ,
			// back
			-1.0
		  , -1.0
		  , -1.0
		  , 1.0
		  , -1.0
		  , -1.0
		  , 1.0
		  , 1.0
		  , -1.0
		  , -1.0
		  , 1.0
		  , -1.0
		};

		constexpr GLuint Indices[] = {
			// front
			0
		  , 1
		  , 2
		  , 2
		  , 3
		  , 0
		   ,
			// right
			1
		  , 5
		  , 6
		  , 6
		  , 2
		  , 1
		   ,
			// back
			7
		  , 6
		  , 5
		  , 5
		  , 4
		  , 7
		   ,
			// left
			4
		  , 0
		  , 3
		  , 3
		  , 7
		  , 4
		   ,
			// bottom
			4
		  , 5
		  , 1
		  , 1
		  , 0
		  , 4
		   ,
			// top
			3
		  , 2
		  , 6
		  , 6
		  , 7
		  , 3
		};

		// Vertex Buffer Object
		mVBO = std::make_unique<VertexBuffer>();
		mVBO->Bind();
		mVBO->FillBuffer(Vertices, sizeof(Vertices));
		mVBO->AddVBElement<float>(3);

		// Vertex Attribute Object
		mVAO = std::make_unique<VertexArray>();
		mVAO->Bind();
		mVAO->AddVBO(*mVBO);

		// Index Buffer Object
		mIBO = std::make_unique<IndexBuffer>();
		mIBO->FillBuffer(Indices, 36);
		mIBO->Bind();
	}

	void RenderManager::Render()
	{
		mClearColor = gGUIManager.GetClearColor();
		mObjectColor = gGUIManager.GetObjectColor();
		mCamera->SetPosition(gGUIManager.GetCameraPosition());
		mCamera->SetRotation(gGUIManager.GetCameraPitch(), gGUIManager.GetCameraYaw());

		// Model Matrix
		static glm::mat4 ModelMatrix = translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0, -10.0));

		// Send our transformation to the currently bound shader
		mShader->SetUniformMat4f("u_ProjectionMatrix", mCamera->GetProjectionMatrix());
		mShader->SetUniformMat4f("u_ViewMatrix", mCamera->GetViewMatrix());
		mShader->SetUniformMat4f("u_ModelMatrix", ModelMatrix);
		mShader->SetUniform4f("u_Color", mObjectColor.x, mObjectColor.y, mObjectColor.z, mObjectColor.w);

		// Rendering
		ImGui::Render();
		I32 Width, Height;
		glfwGetFramebufferSize(gGUIManager.GetGLFWWindow(), &Width, &Height);
		gGUIManager.SetDisplayWidth(Width);
		gGUIManager.SetDisplayHeight(Height);

		glViewport(0, 0, Width, Height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(mClearColor.x, mClearColor.y, mClearColor.z, mClearColor.w);
		glDrawElements(GL_TRIANGLES, mIBO->GetCount(), GL_UNSIGNED_INT, nullptr);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(gGUIManager.GetGLFWWindow());
	}

	void RenderManager::ShutDown() { }
}
