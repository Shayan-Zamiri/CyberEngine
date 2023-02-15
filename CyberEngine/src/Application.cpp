/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "Application.h"
#include "FileManager.h"
#include "GUIManager.h"
#include "InputManager.h"
#include "RenderManager.h"
#include <chrono>
#include "optick.h"

namespace CE
{
	// GLOBAL VARIABLES

	RenderManager gRenderManager;
	GUIManager gGUIManager;
	FileManager gFileManager;
	InputManager gInputManager;

	// FUNCTIONS

	void Application::Run()
	{
		// Order is important!

		gFileManager.StartUp();
		gGUIManager.StartUp();
		gInputManager.StartUp();
		gRenderManager.StartUp();

		std::chrono::time_point<std::chrono::high_resolution_clock> prevTime =
			std::chrono::high_resolution_clock::now();

		while (!gGUIManager.GLFWWindowShouldClose())
		{
			OPTICK_FRAME("MainThread");
			std::chrono::time_point<std::chrono::high_resolution_clock> newTime =
				std::chrono::high_resolution_clock::now();
			std::chrono::duration<float> deltaTime = newTime - prevTime;
			prevTime = newTime;

			gGUIManager.Draw();
			gRenderManager.Render(deltaTime.count());
		}

		gRenderManager.ShutDown();
		gInputManager.ShutDown();
		gGUIManager.ShutDown();
		gFileManager.ShutDown();
	}
}
