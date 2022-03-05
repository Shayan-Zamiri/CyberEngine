#pragma once

#include "CEPCH.h"

namespace CE
{
	class IndexBuffer
	{
	public:
		//CTOR & DTOR
		IndexBuffer(const U32* pData, U32 pCount);

		~IndexBuffer();

		//FUNCTIONS
		void Bind() const;

		void UnBind() const;

		//GETTERS & SETTERS
		U32 GetCount() const { return mCount; }

		//PROPERTIES
	private:
		U32 mRendererID;
		U32 mCount;
		const U32* mData;
	};
}
