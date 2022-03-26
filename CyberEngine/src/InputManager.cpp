/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "InputManager.h"
#include "GUIManager.h"
#include "GLFW/glfw3.h"

namespace CE
{
	// STATICS

	EKeys InputManager::mLastKeyPressed;

	void InputManager::GLFWKeySetCallback(GLFWwindow* pWindow, I32 pKey, I32 pScanCode, I32 pAction, I32 pMods) { }

	void InputManager::GLFWSetMouseButtonCallback(GLFWwindow* pWindow, I32 pButton, I32 pAction, I32 pModes) { }

	void InputManager::GLFWSetScrollCallback(GLFWwindow* pWindow, double pXOffset, double pYOffset) { }

	bool InputManager::CheckKeyState(EKeys pKey, bool pIsPressed)
	{
		const I32 Key = static_cast<I32>(pKey);

		if (0 <= Key && Key <= 7)
			return glfwGetMouseButton(gGUIManager.GetGLFWWindow(), static_cast<int>(pKey)) == pIsPressed;
		else
			return glfwGetKey(gGUIManager.GetGLFWWindow(), Key) == pIsPressed;
	}

	void InputManager::GetMousePos(double& pXPos, double& pYPos)
	{
		glfwGetCursorPos(gGUIManager.GetGLFWWindow(), &pXPos, &pYPos);
	}

	void InputManager::SetMouseRawMotionInputMode(bool pRawMotion)
	{
		if (glfwRawMouseMotionSupported())
		{
			glfwSetInputMode(gGUIManager.GetGLFWWindow(), GLFW_RAW_MOUSE_MOTION, pRawMotion);
		}
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	InputManager::InputManager()
	{
		// Nothing
	}

	InputManager::~InputManager()
	{
		// Nothing
	}

	void InputManager::StartUp()
	{
		glfwSetKeyCallback(gGUIManager.GetGLFWWindow(), GLFWKeySetCallback);
		glfwSetMouseButtonCallback(gGUIManager.GetGLFWWindow(), GLFWSetMouseButtonCallback);
		glfwSetScrollCallback(gGUIManager.GetGLFWWindow(), GLFWSetScrollCallback);

		SetMouseRawMotionInputMode(true);
	}

	void InputManager::ShutDown() { }
}
