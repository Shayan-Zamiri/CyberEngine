/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "IManager.h"
#include "vec4.hpp"
#include "glad/glad.h"

namespace CE
{
	class VertexArray;
	class VertexBuffer;
	class IndexBuffer;
	class Shader;
	class Camera;
	class Model;

	class RenderManager : public IManager
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		RenderManager();

		virtual ~RenderManager() override;

		virtual void StartUp() override;

		virtual void ShutDown() override;

		// FUNCTIONS
	public:
		void Render(float pDeltaTime);

		// GETTERS & SETTERS
	public:
		const glm::vec4& GetClearColor() const { return mClearColor; }

		void SetClearColor(const glm::vec4& pClearColor) { mClearColor = pClearColor; }

		// PROPERTIES
	private:
		const GLubyte* mRendererName;
		const GLubyte* mOpenGLVersion;
		std::unique_ptr<Shader> mShader;
		std::unique_ptr<Camera> mCamera;
		std::unique_ptr<Model> mModel;
		std::string mGLSLVersion;
		glm::vec4 mClearColor;
	};

	extern RenderManager gRenderManager;
}
