#pragma once

#include "CEPCH.h"
#include "glad/glad.h"
#include <vector>

namespace CE
{
	struct VertexBufferElement
	{
		GLint mCount;
		GLenum mType;
		GLboolean mNormalized;

		static GLenum GetSizeOfType(GLenum type)
		{
			switch (type)
			{
				case GL_FLOAT:
				case GL_UNSIGNED_INT:
					return 4;
				case GL_UNSIGNED_BYTE:
					return 1;
				default:
					assert(false);
					return 0;
			}
		}
	};

	class VertexBuffer
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		VertexBuffer();

		virtual ~VertexBuffer();

		// FUNCTIONS
	public:
		static void UnBind();

		void FillBuffer(const void* pData, GLsizei pSize);

		void Bind() const;

		template <typename T>
		void AddVBElement(GLsizei pCount);

		template <>
		void AddVBElement<GLfloat>(GLsizei pCount);

		template <>
		void AddVBElement<GLuint>(GLsizei pCount);

		template <>
		void AddVBElement<GLchar>(GLsizei pCount);

		// GETTERS & SETTERS
	public:
		GLsizei GetStride() const { return mStride; }

		const std::vector<VertexBufferElement>& GetElements() const { return mElements; }

		// PROPERTIES
	private:
		GLuint mRendererID;
		GLsizei mStride;
		GLsizei mSize;
		std::vector<VertexBufferElement> mElements;
	};

	// TEMPLATES

	template <>
	void VertexBuffer::AddVBElement<GLfloat>(GLsizei pCount)
	{
		mElements.push_back({pCount,GL_FLOAT,GL_FALSE});
		mStride += pCount * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template <>
	void VertexBuffer::AddVBElement<GLuint>(GLsizei pCount)
	{
		mElements.push_back({pCount,GL_UNSIGNED_INT,GL_FALSE});
		mStride += pCount * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template <>
	void VertexBuffer::AddVBElement<GLchar>(GLsizei pCount)
	{
		mElements.push_back({pCount,GL_UNSIGNED_BYTE,GL_TRUE});
		mStride += pCount * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
}
