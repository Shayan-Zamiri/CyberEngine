/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "FileManager.h"
#include <fstream>
#include <sstream>
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "assimp/BaseImporter.h"
#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include "assimp/Importer.hpp"

namespace CE
{
	// STATICS

	Assimp::Importer FileManager::sAssimpImporter;

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

	U8* FileManager::LoadImage(const std::string& pFilePath, I32& pOutWidth, I32& pOutHeight, I32& pChannels)
	{
		GLubyte* Data = stbi_load(pFilePath.c_str(), &pOutWidth, &pOutHeight, &pChannels, 0);
		return Data;
	}

	const aiScene* FileManager::LoadAssimpScene(const std::string& pFilePath)
	{
		FreeLastAssimpScene();

		// Read file via assimp
		const aiScene* Scene = sAssimpImporter.ReadFile(pFilePath, aiProcess_Triangulate | aiProcess_GenSmoothNormals |
		                                                aiProcess_FlipUVs | aiProcess_CalcTangentSpace);
		// Check for errors
		if (!Scene || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !Scene->mRootNode) // if is Not Zero
		{
			spdlog::error("Assimp: {} ", sAssimpImporter.GetErrorString());
			return nullptr;
		}

		return Scene;
	}

	void FileManager::FreeLastAssimpScene()
	{
		sAssimpImporter.FreeScene();
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	void FileManager::StartUp()
	{
		// tell stb_image.h to flip loaded texture's on the y-axis
		stbi_set_flip_vertically_on_load(true);
	}

	void FileManager::ShutDown() {}
}
