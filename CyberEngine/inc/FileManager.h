/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "IManager.h"

struct aiScene;

namespace Assimp
{
	class Importer;
}

namespace CE
{
	class FileManager : public IManager
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		FileManager() = default;

		virtual ~FileManager() override = default;

		void StartUp() override;

		void ShutDown() override;

		// FUNCTIONS
	public:
		static std::string FileToString(const std::string& pFilePath);

		static U8* LoadImage(const std::string& pFilePath, I32& pOutWidth, I32& pOutHeight, I32& pChannels);

		static const aiScene* LoadAssimpScene(const std::string& pFilePath);

		static void FreeLastAssimpScene();

		static Assimp::Importer sAssimpImporter;
	};

	extern FileManager gFileManager;
}
