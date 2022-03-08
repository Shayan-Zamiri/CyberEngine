#include "CEPCH.h"
#include "VertexArray.h"
#include "VertexBuffer.h"

namespace CE
{
	// STATICS

	void VertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

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

	void VertexArray::AddVBO(const VertexBuffer& pVBO) const
	{
		Bind();
		const auto& Elements = pVBO.GetElements();
		GLuint Offset = 0;
		for (GLuint i = 0; i < Elements.size(); i++)
		{
			glEnableVertexArrayAttrib(mRendererID, i);
			glVertexAttribPointer(i, Elements[i].mCount, Elements[i].mType, Elements[i].mNormalized, pVBO.GetStride()
			                    , reinterpret_cast<const void*>(Offset));
			Offset += Elements[i].mCount * VertexBufferElement::GetSizeOfType(Elements[i].mType);
		}
	}
}
