/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

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
