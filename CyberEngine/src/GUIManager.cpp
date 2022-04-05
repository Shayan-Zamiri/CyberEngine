/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "RenderManager.h"
#include "GUIManager.h"
#include "Camera.h"
#include "imgui.h"
#include "InputManager.h"
#include "glm/glm.hpp"
#include "GLFW/glfw3.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "InputManager.h"

namespace CE
{
	// STATICS

	void GUIManager::GlFWErrorCallback(I32 pError, const char* pDescription)
	{
		spdlog::error("GLFW Error {}: {}\n", pError, pDescription);
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	GUIManager::GUIManager() {}

	GUIManager::~GUIManager() {}

	void GUIManager::StartUp()
	{
		glfwSetErrorCallback(GlFWErrorCallback);
		if (!glfwInit())
		{
			return;
		}

		glfwWindowHint(GLFW_SAMPLES, 16);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Create window with graphics context
		mDisplayWidth = 1280;
		mDisplayHeight = 720;
		mGLFWWindow = glfwCreateWindow(mDisplayWidth, mDisplayHeight, "Cyber Engine", nullptr, nullptr);
		if (mGLFWWindow == nullptr)
		{
			return;
		}
		glfwMakeContextCurrent(mGLFWWindow);

		// Enable vsync
		glfwSwapInterval(1);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		mImGuiIO = std::make_unique<ImGuiIO>(ImGui::GetIO());
		(void)mImGuiIO;
		mImGuiIO->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();

		// Default Values
		mClearColor = glm::vec4{0.3f, 0.4f, 0.7f, 1.0f};
		mCameraPosition = glm::vec3{0.0f, 0.0f, 0.0f};
		mCameraPitch = 0.0f;
		mCameraYaw = Camera::sDefaultYaw;
	}

	void GUIManager::ShutDown()
	{
		// Cleanup ImGUI
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();

		// Cleanup GLFW
		glfwDestroyWindow(mGLFWWindow);
		glfwTerminate();
	}

	// FUNCTIONS

	void GUIManager::Draw()
	{
		// Poll and handle events (inputs, window resize, etc.)
		// You can read the io.WantCaptureMouse, io.WantCaptureKeyboard flags to tell if dear imgui wants to use your inputs.
		// - When io.WantCaptureMouse is true, do not dispatch mouse input data to your main application, or clear/overwrite your copy of the mouse data.
		// - When io.WantCaptureKeyboard is true, do not dispatch keyboard input data to your main application, or clear/overwrite your copy of the keyboard data.
		// Generally you may always pass all inputs to dear imgui, and hide them from your application based on those two flags.
		glfwPollEvents();

		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// Show a simple window
		{
			ImGui::Begin("Setup background color"); // Create a window called "Hello, world!" and append into it.

			ImGui::ColorEdit4("Clear Color", reinterpret_cast<float*>(&mClearColor));
			ImGui::DragFloat3("Camera Position:", &mCameraPosition[0]);
			ImGui::DragFloat("Camera Pitch:", &mCameraPitch, 0.5f, -90.0f, 90.0f);
			ImGui::DragFloat("Camera Yaw:", &mCameraYaw, 0.5f, 360.0f, 360.0f);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate
			          , ImGui::GetIO().Framerate);
			ImGui::End();
		}
	}

	bool GUIManager::GLFWWindowShouldClose() const
	{
		return glfwWindowShouldClose(mGLFWWindow);
	}
}
