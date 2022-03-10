#include "CEPCH.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>

namespace CE
{
	// STATICS

	std::string FileManager::FileToString(const std::string& pFilePath)
	{
		std::ifstream Stream{pFilePath.c_str()};

		if (Stream.fail())
			spdlog::error("Failed to open file");

		std::string Line;
		std::string Content;

		while (std::getline(Stream, Line))
		{
			Content.append(Line + '\n');
		}

		return Content;
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	void FileManager::StartUp() {}

	void FileManager::ShutDown() {}
}
