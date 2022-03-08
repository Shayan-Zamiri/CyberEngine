#include "CEPCH.h"
#include "Application.h"
#include "GUIManager.h"
#include "RenderManager.h"

namespace CE
{
	// GLOBAL VARIABLES

	RenderManager gRenderManager;
	GUIManager gGUIManager;

	// FUNCTIONS

	void Application::Run()
	{
		gGUIManager.StartUp();
		gRenderManager.StartUp();

		while (!gGUIManager.GLFWWindowShouldClose())
		{
			gGUIManager.Draw();
			gRenderManager.Render();
		}

		gRenderManager.ShutDown();
		gGUIManager.ShutDown();
	}
}
