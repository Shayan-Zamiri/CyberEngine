/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "IManager.h"

namespace CE
{
	class FileManager : public IManager
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		FileManager() = default;

		virtual ~FileManager() = default;

		virtual void StartUp() override;

		virtual void ShutDown() override;

		// FUNCTIONS
	public:
		static std::string FileToString(const std::string& pFilePath);
	};

	extern FileManager gFileManager;
}
