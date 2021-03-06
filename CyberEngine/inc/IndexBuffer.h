/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "glad/glad.h"

namespace CE
{
	class IndexBuffer
	{
	public:
		//CTOR & DTOR
		IndexBuffer();

		virtual ~IndexBuffer();

		//FUNCTIONS
	public:
		void FillBuffer(const std::vector<GLuint>& pIndices);

		void Bind() const;

		void UnBind() const;

		//GETTERS & SETTERS
	public:
		GLsizei GetCount() const { return mCount; }

		//PROPERTIES
	private:
		GLuint mRendererID;
		GLsizei mCount;
	};
}
