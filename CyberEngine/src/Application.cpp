#include "CEPCH.h"
#include "Application.h"
#include "FileManager.h"
#include "GUIManager.h"
#include "RenderManager.h"

namespace CE
{
	// GLOBAL VARIABLES

	RenderManager gRenderManager;
	GUIManager gGUIManager;
	FileManager gFileManager;

	// FUNCTIONS

	void Application::Run()
	{
		gFileManager.StartUp();
		gGUIManager.StartUp();
		gRenderManager.StartUp();

		while (!gGUIManager.GLFWWindowShouldClose())
		{
			gGUIManager.Draw();
			gRenderManager.Render();
		}

		gRenderManager.ShutDown();
		gGUIManager.ShutDown();
		gFileManager.ShutDown();
	}
}
