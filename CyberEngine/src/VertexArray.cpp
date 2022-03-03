#include "CEPCH.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "glad/glad.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	VertexArray::VertexArray()
	{
		glGenVertexArrays(1, &mRendererID);
	}

	VertexArray::~VertexArray()
	{
		glDeleteVertexArrays(1, &mRendererID);
	}

	// FUNCTIONS

	void VertexArray::Bind() const
	{
		glBindVertexArray(mRendererID);
	}

	void VertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}

	void VertexArray::AddBuffer(const VertexBuffer& pVB)
	{
		Bind();
		pVB.Bind();
		const auto& Elements = pVB.GetElements();
		U32 Offset = 0;
		for (U32 i = 0; i < Elements.size(); i++)
		{
			glEnableVertexAttribArray(i);
			glVertexAttribPointer(i, Elements[i].mCount, Elements[i].mType, Elements[i].mNormalized, pVB.GetStride()
			                    , reinterpret_cast<const void*>(Offset));
			Offset += Elements[i].mCount * VertexBufferElement::GetSizeOfType(Elements[i].mType);
		}
	}
}
