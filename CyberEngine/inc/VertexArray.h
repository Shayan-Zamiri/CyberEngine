/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "glad/glad.h"

namespace CE
{
	class VertexBuffer;
	class IndexBuffer;

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

		void AttachVBO(const VertexBuffer& pVBO) const;

		// PROPERTIES
	private:
		GLuint mRendererID;
	};
}
