/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include <set>

struct aiMaterial;
struct aiMesh;
struct aiScene;
struct aiNode;
enum aiTextureType;

namespace CE
{
	class Texture;
	class Mesh;
	class Shader;

	class Model
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		Model() = default	;

		virtual ~Model() = default;

		// FUNCTIONS
	public:
		void Draw() const;

		void LoadModel(const std::string& pFilePath);

		void SetupMeshesTextures(const Shader& pShader);

		void ProcessNode(const aiNode* pNode, const aiScene* pScene);

		Mesh ProcessMesh(aiMesh* pMesh, const aiScene* pScene);

		std::vector<std::shared_ptr<Texture>> LoadMaterialTextures(aiMaterial* pMat, aiTextureType pType);

		// GETTERS & SETTERS
	public:
		// PROPERTIES
	private:
		std::string mFilePath;
		std::string mDirectory;
		std::vector<std::shared_ptr<Texture>> mLoadedTextures; // To prevent loading the same texture
		std::vector<Mesh> mMeshes;
	};
}
