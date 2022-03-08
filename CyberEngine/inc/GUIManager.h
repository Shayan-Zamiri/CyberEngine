#pragma once

#include "CEPCH.h"
#include "IManager.h"
#include "GLFW/glfw3.h"

struct ImGuiIO;

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
		void Draw();

		bool GLFWWindowShouldClose() const;

	private:
		static void GlFWErrorCallback(I32 pError, const char* pDescription);

		// GETTERS & SETTERS
	public:
		GLFWwindow* GetGLFWWindow() const { return mGLFWWindow; }

		void SetDisplayWidth(I32 pDisplayWidth) { mDisplayWidth = pDisplayWidth; }

		void SetDisplayHeight(I32 pDisplayHeight) { mDisplayHeight = pDisplayHeight; }

		// PROPERTIES
	private:
		I32 mDisplayWidth;
		I32 mDisplayHeight;
		GLFWwindow* mGLFWWindow;
		std::unique_ptr<ImGuiIO> mImGuiIO;
	};

	extern GUIManager gGUIManager;
}
