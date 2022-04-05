/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "IndexBuffer.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	IndexBuffer::IndexBuffer()
	{
		glGenBuffers(1, &mRendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	// FUNCTIONS

	void IndexBuffer::FillBuffer(const std::vector<GLuint>& pIndices)
	{
		mCount = pIndices.size();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(GLuint), &pIndices[0],GL_STATIC_DRAW);
	}

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
	}

	void IndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
