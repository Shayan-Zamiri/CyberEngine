/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "IManager.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"

struct ImGuiIO;
struct GLFWwindow;

namespace CE
{
	class GUIManager : public IManager
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		GUIManager();

		virtual ~GUIManager() override;

		void StartUp() override;

		void ShutDown() override;

		// FUNCTIONS
	public:
		static void GlFWErrorCallback(I32 pError, const char* pDescription);

		void Draw();

		bool GLFWWindowShouldClose() const;

		// GETTERS & SETTERS
	public:
		GLFWwindow* GetGLFWWindow() const { return mGLFWWindow; }

		void SetDisplayWidth(I32 pDisplayWidth) { mDisplayWidth = pDisplayWidth; }

		void SetDisplayHeight(I32 pDisplayHeight) { mDisplayHeight = pDisplayHeight; }

		I32 GetDisplayWidth() const { return mDisplayWidth; }

		I32 GetDisplayHeight() const { return mDisplayHeight; }

		const glm::vec4& GetClearColor() const { return mClearColor; }

		const glm::vec3& GetCameraPosition() const { return mCameraPosition; }

		float GetCameraPitch() const { return mCameraPitch; }

		float GetCameraYaw() const { return mCameraYaw; }

		// PROPERTIES
	private:
		I32 mDisplayWidth;
		I32 mDisplayHeight;
		GLFWwindow* mGLFWWindow;
		std::unique_ptr<ImGuiIO> mImGuiIO;

		// Visible Properties
		glm::vec4 mClearColor;
		glm::vec3 mCameraPosition;
		float mCameraPitch;
		float mCameraYaw;
	};

	extern GUIManager gGUIManager;
}
