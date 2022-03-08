#include "CEPCH.h"
#include "VertexBuffer.h"

namespace CE
{
	// STATICS

	void VertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	VertexBuffer::VertexBuffer() : mRendererID{0}, mStride{0}
	{
		glGenBuffers(1, &mRendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	// FUNCTIONS

	void VertexBuffer::FillBuffer(const void* pData, GLsizei pSize)
	{
		mSize = pSize;
		glNamedBufferData(mRendererID, pSize, pData, GL_STATIC_DRAW);
	}

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
	}
}
