/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "glm/glm.hpp"

namespace CE
{
	class Camera
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		Camera();

		Camera(const glm::vec3& pPosition, float pPitch, float pYaw, const glm::vec3& pWorldUp);

		virtual ~Camera() = default;

		// FUNCTIONS
	public:
		glm::mat4 GetViewMatrix();

	private:
		void UpdateDirectionVectors();

		// GETTERS & SETTERS
	public:
		const glm::mat4& GetProjectionMatrix() const { return mProjection; }

		void SetPosition(const glm::vec3& pPosition);

		void SetRotation(float pPitch, float pYaw);

		// PROPERTIES
	public:
		/** Pitch,Yaw,Roll */
		static constexpr glm::vec3 sDefaultWorldUp{0.0f, 1.0f, 0.0f};
		static constexpr float sDefaultYaw{-90.0f};
		static constexpr float sDefaultFOV{60.0f};
		static constexpr float sDefaultAspectRatio{1920.0f / 1080.0f};
		static constexpr float sDefaultNear{0.1f};
		static constexpr float sDefaultFar{100.0f};

	private:
		glm::vec3 mPosition;

		float mPitch;
		float mYaw;

		glm::vec3 mForward;
		glm::vec3 mRight;
		glm::vec3 mUp;

		glm::vec3 mWorldUp;

		glm::mat4 mProjection;
	};
}
