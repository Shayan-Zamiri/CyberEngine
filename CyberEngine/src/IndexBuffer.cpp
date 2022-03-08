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

	void IndexBuffer::FillBuffer(const GLuint* pData, GLuint pCount)
	{
		mCount = pCount;
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, pCount * sizeof(GLuint), pData,GL_STATIC_DRAW);
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
