#include "CEPCH.h"
#include "Application.h"

#include "RenderManager.h"

namespace CE
{
	// GLOBAL VARIABLES

	RenderManager gRenderManager;

	// FUNCTIONS

	void Application::Run()
	{
		gRenderManager.StartUp();
		gRenderManager.Render();
		gRenderManager.ShutDown();
	}
}
