#pragma once

#include "CEPCH.h"

namespace CE
{
	class MemAllocator
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		MemAllocator() = default;

		virtual ~MemAllocator() = default;

		virtual void* Alloc() = 0;

		virtual void Free() = 0;
	};
}
