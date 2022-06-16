/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"

namespace CE
{
	class VertexArray;
	class VertexBuffer;

	class Scene
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		// FUNCTIONS
	private:
		// GETTERS & SETTERS
	public:
		// PROPERTIES
	private:
		std::unique_ptr<VertexArray> VAO;
		std::vector<std::unique_ptr<VertexBuffer>> VBOs;
	};
}
