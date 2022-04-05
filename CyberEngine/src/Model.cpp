/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "Model.h"
#include "FileManager.h"
#include "Mesh.h"
#include "Texture.h"
#include "assimp/mesh.h"
#include "assimp/scene.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	// FUNCTIONS

	void Model::Draw() const
	{
		for (size_t i = 0; i < mMeshes.size(); i++)
		{
			mMeshes[i].Draw();
		}
	}

	void Model::LoadModel(const std::string& pFilePath)
	{
		if (const aiScene* assimpScene = FileManager::LoadAssimpScene(pFilePath))
		{
			mDirectory = pFilePath.substr(0, pFilePath.find_last_of('/'));
			const aiNode* rootNode = assimpScene->mRootNode;
			ProcessNode(rootNode, assimpScene);
		}
		FileManager::FreeLastAssimpScene();
	}

	void Model::SetupMeshesTextures(const Shader& pShader)
	{
		for (size_t i = 0; i < mMeshes.size(); i++)
		{
			mMeshes[i].SetupTextures(pShader);
		}
	}

	void Model::ProcessNode(const aiNode* pNode, const aiScene* pScene)
	{
		// Process each mesh located at the current node
		for (U32 i = 0; i < pNode->mNumMeshes; i++)
		{
			// The node object only contains indices to index the actual objects in the scene. 
			// The scene contains all the data, node is just to keep stuff organized (like relations between nodes).
			aiMesh* mesh = pScene->mMeshes[pNode->mMeshes[i]];
			mMeshes.push_back(ProcessMesh(mesh, pScene));
		}

		// After we've processed all of the meshes (if any) we then recursively process each of the children nodes
		for (U32 i = 0; i < pNode->mNumChildren; i++)
		{
			ProcessNode(pNode->mChildren[i], pScene);
		}
	}

	Mesh Model::ProcessMesh(aiMesh* pMesh, const aiScene* pScene)
	{
		// Data to fill
		std::vector<Vertex> vertices;
		std::vector<GLuint> indices;
		std::vector<std::shared_ptr<Texture>> textures;

		// Walk through each of the mesh's vertices
		for (GLuint i = 0; i < pMesh->mNumVertices; i++)
		{
			Vertex vertex{};
			glm::vec3 Vector;
			// We declare a placeholder vector since assimp uses its own vector class that doesn't directly 
			// convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
			// Positions
			Vector.x = pMesh->mVertices[i].x;
			Vector.y = pMesh->mVertices[i].y;
			Vector.z = pMesh->mVertices[i].z;
			vertex.mPosition = Vector;

			// Normals
			if (pMesh->HasNormals())
			{
				Vector.x = pMesh->mNormals[i].x;
				Vector.y = pMesh->mNormals[i].y;
				Vector.z = pMesh->mNormals[i].z;
				vertex.mNormal = Vector;
			}

			// Texture Coordinates
			if (pMesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
			{
				glm::vec2 vec;
				// A vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't 
				// use models where a vertex can have multiple texture coordinates so we always take the first set (0).
				vec.x = pMesh->mTextureCoords[0][i].x;
				vec.y = pMesh->mTextureCoords[0][i].y;
				vertex.mTexCoords = vec;
			}
			else
				vertex.mTexCoords = glm::vec2(0.0f, 0.0f);

			vertices.push_back(vertex);
		}

		// Now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
		for (GLuint i = 0; i < pMesh->mNumFaces; i++)
		{
			aiFace Face = pMesh->mFaces[i];
			// Retrieve all indices of the face and store them in the indices vector
			for (GLuint j = 0; j < Face.mNumIndices; j++)
				indices.push_back(Face.mIndices[j]);
		}

		// Process materials
		aiMaterial* Material = pScene->mMaterials[pMesh->mMaterialIndex];

		// We assume a convention for sampler names in the shaders. Each diffuse texture should be named
		// as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
		// Same applies to other texture as the following list summarizes:
		// Diffuse: texture_diffuseN
		// Specular: texture_specularN
		// Normal: texture_normalN

		// 1. Diffuse maps
		std::vector<std::shared_ptr<Texture>> DiffuseMap = LoadMaterialTextures(Material, aiTextureType_DIFFUSE);
		textures.insert(textures.end(), DiffuseMap.begin(), DiffuseMap.end());
		// 2. Specular maps
		std::vector<std::shared_ptr<Texture>> SpecularMaps = LoadMaterialTextures(Material, aiTextureType_SPECULAR);
		textures.insert(textures.end(), SpecularMaps.begin(), SpecularMaps.end());
		// 3. Normal maps
		std::vector<std::shared_ptr<Texture>> NormalMaps = LoadMaterialTextures(Material, aiTextureType_HEIGHT);
		textures.insert(textures.end(), NormalMaps.begin(), NormalMaps.end());
		// 4. Height maps
		std::vector<std::shared_ptr<Texture>> HeightMaps = LoadMaterialTextures(Material, aiTextureType_AMBIENT);
		textures.insert(textures.end(), HeightMaps.begin(), HeightMaps.end());

		// Return a mesh object created from the extracted mesh data
		return Mesh{vertices, indices, textures};
	}

	std::vector<std::shared_ptr<Texture>> Model::LoadMaterialTextures(aiMaterial* pMat, aiTextureType pType)
	{
		std::vector<std::shared_ptr<Texture>> textures;
		for (GLuint i = 0; i < pMat->GetTextureCount(pType); i++)
		{
			aiString str;
			pMat->GetTexture(pType, i, &str);
			// check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
			bool skip = false;
			for (GLuint j = 0; j < mLoadedTextures.size(); j++)
			{
				if (std::strcmp(mLoadedTextures[j]->GetFilePath().data(),
				                (mDirectory + '/' + str.C_Str()).c_str()) == 0)
				{
					textures.push_back(mLoadedTextures[j]);
					skip = true;
					// A texture with the same filepath has already been loaded, continue to next one. (optimization)
					break;
				}
			}
			if (!skip)
			{
				// If texture hasn't been loaded already, load it
				std::shared_ptr<Texture> texture = std::make_shared<Texture>();
				if (texture->LoadTexture(mDirectory + '/' + str.C_Str()))
				{
					texture->SetType(static_cast<ETextureType>(pType));
					textures.push_back(texture);
					// Store it as texture loaded for entire model, to ensure we won't unnecessary load duplicate textures.
					mLoadedTextures.push_back(texture);
				}
				else
				{
					spdlog::error("Failed to load Texture, path: {}.", str.C_Str());
				}
			}
		}
		return textures;
	}
}
