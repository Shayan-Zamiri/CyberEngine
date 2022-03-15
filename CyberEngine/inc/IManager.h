/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"

namespace CE
{
	class IManager
	{
	public:
		virtual ~IManager() = default;

		virtual void StartUp() = 0;

		virtual void ShutDown() = 0;
	};
}
