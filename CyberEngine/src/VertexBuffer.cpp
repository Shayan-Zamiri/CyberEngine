/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "VertexBuffer.h"
#include "Mesh.h"

namespace CE
{
	// STATICS

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	VertexBuffer::VertexBuffer() : mRendererID{0}, mSize{0}
	{
		glGenBuffers(1, &mRendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	// FUNCTIONS

	void VertexBuffer::FillBuffer(const std::vector<Vertex>& pVertices)
	{
		mCount = pVertices.size();
		mSize = mCount * sizeof(Vertex);
		glNamedBufferData(mRendererID, mSize, &pVertices[0], GL_STATIC_DRAW);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	}
}
