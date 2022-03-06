#pragma once

#include "CEPCH.h"

namespace CE
{
	class VertexBuffer;

	class VertexArray
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		VertexArray();

		virtual ~VertexArray();

		// FUNCTIONS
	public:
		void Bind() const;

		void UnBind() const;

		void AddBuffer(const VertexBuffer& pVBO);

		// PROPERTIES
	private:
		U32 mRendererID;
	};
}
