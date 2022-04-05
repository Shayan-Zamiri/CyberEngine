/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "glad/glad.h"
#include <vector>

namespace CE
{
	struct Vertex;

	class VertexBuffer
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		VertexBuffer();

		virtual ~VertexBuffer();

		// FUNCTIONS
	public:
		static void UnBind();

		void FillBuffer(const std::vector<Vertex>& pVertices);

		void Bind() const;

		// GETTERS & SETTERS
	public:
		GLsizei GetSize() const { return mSize; }

		GLsizei GetCount() const { return mCount; }

		// PROPERTIES
	private:
		GLuint mRendererID;
		GLsizei mSize;
		GLsizei mCount;
	};
}
