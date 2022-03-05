#include "CEPCH.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	VertexBuffer::VertexBuffer(const void* pData, U32 pSize) : mRendererID{0}, mStride{0}, mSize{pSize}, mData{pData}
	{
		glGenBuffers(1, &mRendererID);
	}

	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &mRendererID);
	}

	// FUNCTIONS

	void VertexBuffer::Bind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, mRendererID);
		glBufferData(GL_ARRAY_BUFFER, mSize, mData, GL_STATIC_DRAW);
	}

	void VertexBuffer::UnBind() const
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	// GETTERS & SETTERS

	U32 VertexBuffer::GetStride() const
	{
		return mStride;
	}

	const std::vector<VertexBufferElement>& VertexBuffer::GetElements() const
	{
		return mElements;
	}
}
