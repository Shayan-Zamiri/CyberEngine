#include "CEPCH.h"
#include "VertexArray.h"

#include "Mesh.h"
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

	void VertexArray::AttachVBO(const VertexBuffer& pVBO) const
	{
		// Positions
		glEnableVertexArrayAttrib(mRendererID, 0);
		glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      reinterpret_cast<void*>(0));

		// Normals
		glEnableVertexArrayAttrib(mRendererID, 1);
		glVertexAttribPointer(1, 3,GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      reinterpret_cast<void*>(offsetof(Vertex, mNormal)));

		// Textures
		glEnableVertexArrayAttrib(mRendererID, 2);
		glVertexAttribPointer(2, 2,GL_FLOAT, GL_FALSE, sizeof(Vertex),
		                      reinterpret_cast<void*>(offsetof(Vertex, mTexCoords)));
	}
}
