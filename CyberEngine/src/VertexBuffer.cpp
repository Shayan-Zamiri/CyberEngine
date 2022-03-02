#include "CEPCH.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	VertexBuffer::VertexBuffer(const void* pData, U32 pSize)
	{
		glGenBuffers(1, &mRendererID);
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, pSize, pData, GL_STATIC_DRAW);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	// FUNCTIONS

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
