/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "Camera.h"
#include "InputManager.h"
#include "ext/matrix_clip_space.hpp"
#include "ext/matrix_transform.hpp"
#include <glm/gtc/quaternion.hpp>

#include "GUIManager.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	Camera::Camera() :
		mPosition{0.0f, 0.0f, 0.0f},
		mPitch{0.0f},
		mYaw{sDefaultYaw},
		mRotationSpeed{sDefaultRotationSpeed},
		mMoveSpeed{sDefaultMoveSpeed},
		mWorldUp{sDefaultWorldUp},
		mProjection{glm::perspective(glm::radians(sDefaultFOV), sDefaultAspectRatio, sDefaultNear, sDefaultFar)}
	{
		UpdateDirectionVectors();
	}

	Camera::Camera(const glm::vec3& pPosition, float pPitch, float pYaw, const glm::vec3& pWorldUp) :
		mPosition{pPosition},
		mPitch{0.0f},
		mYaw{sDefaultYaw},
		mRotationSpeed{sDefaultRotationSpeed},
		mMoveSpeed{sDefaultMoveSpeed},
		mWorldUp{pWorldUp},
		mProjection{glm::perspective(glm::radians(sDefaultFOV), sDefaultAspectRatio, sDefaultNear, sDefaultFar)}
	{
		UpdateDirectionVectors();
	}

	// FUNCTIONS

	void Camera::UpdateDirectionVectors()
	{
		// Forward Vector
		glm::vec3 Forward;
		Forward.x = glm::cos(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
		Forward.y = glm::sin(glm::radians(mPitch));
		Forward.z = glm::sin(glm::radians(mYaw)) * glm::cos(glm::radians(mPitch));
		mForward = glm::normalize(Forward);

		// Right Vector
		mRight = glm::normalize(glm::cross(Forward, mWorldUp));

		// Up Vector
		mUp = glm::normalize(glm::cross(mRight, Forward));
	}

	glm::mat4 Camera::GetViewMatrix()
	{
		UpdateDirectionVectors();
		return glm::lookAt(mPosition, mPosition + mForward, mUp);
	}

	void Camera::Update(float pDeltaTime)
	{
		OPTICK_EVENT("Camera::Update");
		static double xPos, yPos = 0;
		const double prevX = xPos;
		const double prevY = yPos;
		InputManager::GetMousePos(xPos, yPos);
		double deltaX = (xPos - prevX) * pDeltaTime;
		double deltaY = (yPos - prevY) * pDeltaTime;

		if ((glm::abs(deltaX) > 0.1 || glm::abs(deltaY) > 0.1) && InputManager::CheckKeyState(EKeys::MOUSE_BUTTON_RIGHT,
		                                                                                      true))
		{
			SetRotation(mPitch - deltaY * mRotationSpeed, mYaw + deltaX * mRotationSpeed);
		}
		if (InputManager::CheckKeyState(EKeys::W, true))
		{
			SetPosition(mPosition + mForward * (pDeltaTime * mMoveSpeed));
		}
		else if (InputManager::CheckKeyState(EKeys::S, true))
		{
			SetPosition(mPosition - mForward * (pDeltaTime * mMoveSpeed));
		}
		else if (InputManager::CheckKeyState(EKeys::D, true))
		{
			SetPosition(mPosition + mRight * (pDeltaTime * mMoveSpeed));
		}
		else if (InputManager::CheckKeyState(EKeys::A, true))
		{
			SetPosition(mPosition - mRight * (pDeltaTime * mMoveSpeed));
		}
	}

	// GETTERS & SETTERS

	void Camera::SetPosition(const glm::vec3& pPosition)
	{
		mPosition = pPosition;
		UpdateDirectionVectors();
	}

	void Camera::SetRotation(float pPitch, float pYaw)
	{
		// Normalize
		pYaw = fmodf(pYaw, 360.0f);

		if (pYaw < 0.0f)
		{
			pYaw += 360.0f;
		}

		if (pPitch > 89.9f)
		{
			pPitch = 89.9f;
		}
		else if (pPitch < -89.9f)
		{
			pPitch = -89.9f;
		}

		// Set
		mPitch = pPitch;
		mYaw = pYaw;

		UpdateDirectionVectors();
	}
}
