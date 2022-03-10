#pragma once

#include "CEPCH.h"
#include "IManager.h"
#include "vec4.hpp"
#include "glad/glad.h"
#include "Shader.h"

namespace CE
{
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
		void Render();

		// GETTERS & SETTERS
	public:
		const glm::vec4& GetClearColor() const { return mClearColor; }

		void SetClearColor(const glm::vec4& pClearColor) { mClearColor = pClearColor; }

		// PROPERTIES
	public:
		glm::vec3 mWorld;
		glm::vec3 mOrigin;
		glm::vec4 mClearColor;
		glm::vec4 mObjectColor;
	private:
		std::string mGLSLVersion;
		const GLubyte* mRendererName;
		const GLubyte* mOpenGLVersion;
		std::unique_ptr<Shader> mShader;
	};

	extern RenderManager gRenderManager;
}
