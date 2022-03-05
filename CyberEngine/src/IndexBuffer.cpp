#include "CEPCH.h"
#include "IndexBuffer.h"

#include "glad/glad.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	IndexBuffer::IndexBuffer(const U32* pData, U32 pCount) : mCount{pCount}, mData{pData}
	{
		glGenBuffers(1, &mRendererID);
	}

	IndexBuffer::~IndexBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	// FUNCTIONS

	void IndexBuffer::Bind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mCount * sizeof(U32), mData, GL_STATIC_DRAW);
	}

	void IndexBuffer::UnBind() const
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}
