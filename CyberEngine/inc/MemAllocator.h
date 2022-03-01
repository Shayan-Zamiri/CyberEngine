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

		virtual VPTR* Alloc() = 0;

		virtual void Free() = 0;
	};
}
