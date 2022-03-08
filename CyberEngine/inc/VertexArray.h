#pragma once

#include "CEPCH.h"
#include "glad/glad.h"

namespace CE
{
	class VertexBuffer;

	class VertexArray
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		VertexArray();

		virtual ~VertexArray();

		// FUNCTIONS
	public:
		static void UnBind();

		void Bind() const;

		void AddVBO(const VertexBuffer& pVBO) const;

		// PROPERTIES
	private:
		GLuint mRendererID;
	};
}
