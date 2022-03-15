/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"

namespace CE
{
	class MemAllocator
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		MemAllocator(const size_t pTotalSize) : mTotalSize{ pTotalSize } {};

		virtual ~MemAllocator() { mTotalSize = 0; }

		virtual void* Alloc(const size_t pSize, const size_t pAlignment) = 0;

		virtual void Free() = 0;

		// FUNCTIONS
	public:
		inline size_t GetTotalSize() { return mTotalSize; }

		inline size_t GetUsedSize() { return mUsedSize; }

		inline size_t GetPeakSize() { return mPeakSize; }

		//PROPERTIES
	protected:
		size_t mTotalSize;
		size_t mUsedSize;
		size_t mPeakSize;
	};
}
