#pragma once

#include "CEPCH.h"
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
