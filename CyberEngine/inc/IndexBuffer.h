#pragma once

#include "CEPCH.h"
#include "glad/glad.h"

namespace CE
{
	class IndexBuffer
	{
	public:
		//CTOR & DTOR
		IndexBuffer();

		~IndexBuffer();

		//FUNCTIONS
	public:
		void FillBuffer(const GLuint* pData, GLuint pCount);

		void Bind() const;

		void UnBind() const;

		//GETTERS & SETTERS
	public:
		GLuint GetCount() const { return mCount; }

		//PROPERTIES
	private:
		GLuint mRendererID;
		GLuint mCount;
	};
}
