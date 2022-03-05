#pragma once

#include "CEPCH.h"
#include "glad/glad.h"
#include <vector>

namespace CE
{
	struct VertexBufferElement
	{
		unsigned int mCount;
		unsigned int mType;
		unsigned char mNormalized;

		static U32 GetSizeOfType(U32 type)
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
		VertexBuffer(const void* pData, U32 pSize);

		virtual ~VertexBuffer();

		// FUNCTIONS
	public:
		void Bind() const;

		void UnBind() const;

		template <typename T>
		void AddVBElement(U32 pCount);

		template <>
		void AddVBElement<float>(U32 pCount);

		template <>
		void AddVBElement<U32>(U32 pCount);

		template <>
		void AddVBElement<signed char>(U32 pCount);

		// GETTERS & SETTERS
	public:
		U32 GetStride() const;

		const std::vector<VertexBufferElement>& GetElements() const;

		// PROPERTIES
	private:
		U32 mRendererID;
		U32 mStride;
		U32 mSize;
		const void* mData;
		std::vector<VertexBufferElement> mElements;
	};

	// TEMPLATES

	template <>
	void VertexBuffer::AddVBElement<float>(U32 pCount)
	{
		mElements.push_back({pCount,GL_FLOAT,GL_FALSE});
		mStride += pCount * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template <>
	void VertexBuffer::AddVBElement<unsigned>(U32 pCount)
	{
		mElements.push_back({pCount,GL_UNSIGNED_INT,GL_FALSE});
		mStride += pCount * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template <>
	void VertexBuffer::AddVBElement<signed char>(U32 pCount)
	{
		mElements.push_back({pCount,GL_UNSIGNED_BYTE,GL_TRUE});
		mStride += pCount * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
}
