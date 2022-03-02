#pragma once

#include "CETypes.h"

namespace CE
{
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

		// PROPERTIES
	private:
		U32 mRendererID;
	};
}
