/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

namespace CE
{
	// CTOR/DTOR & VIRTUAL FUNCTIONS

	Mesh::Mesh(Mesh&& pMesh) noexcept :
		mVAO{std::move(pMesh.mVAO)},
		mVBO{std::move(pMesh.mVBO)},
		mIBO{std::move(pMesh.mIBO)},
		mTextures{std::move(pMesh.mTextures)} {}

	Mesh::Mesh(const std::vector<Vertex>& pVertices, const std::vector<GLuint>& pIndices,
	           std::vector<std::shared_ptr<Texture>> pTextures) : mTextures{std::move(pTextures)}

	{
		mVAO = std::make_unique<VertexArray>();
		mVBO = std::make_unique<VertexBuffer>();
		mIBO = std::make_unique<IndexBuffer>();
		SetupMeshData(pVertices, pIndices);
	}

	// FUNCTIONS

	void Mesh::SetupMeshData(const std::vector<Vertex>& pVertices, const std::vector<GLuint>& pIndices)
	{
		// Vertex Buffer
		mVBO->Bind();
		mVBO->FillBuffer(pVertices);

		// Vertex Array
		mVAO->Bind();
		mVAO->AttachVBO(*mVBO);

		// Index Buffer
		mIBO->Bind();
		mIBO->FillBuffer(pIndices);
	}

	void Mesh::SetupTextures(const Shader& pShader)
	{
		// Bind appropriate textures
		GLuint diffuseNr = 1;
		GLuint specularNr = 1;
		GLuint normalNr = 1;
		GLuint heightNr = 1;
		for (GLuint i = 0; i < mTextures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
			// retrieve texture number (the N in diffuse_textureN)
			std::string number;
			const ETextureType textureType = mTextures[i]->GetType();
			if (textureType == ETextureType::DIFFUSE)
				number = std::to_string(diffuseNr++);
			else if (textureType == ETextureType::SPECULAR)
				number = std::to_string(specularNr++);
			else if (textureType == ETextureType::NORMALS)
				number = std::to_string(normalNr++);
			else if (textureType == ETextureType::HEIGHT)
				number = std::to_string(heightNr++);

			pShader.SetUniform1i(TextureTypeToString(textureType) + number, i);
			// and finally bind the texture
			mTextures[i]->Bind();
		}
	}

	void Mesh::Draw() const
	{
		OPTICK_EVENT("Mesh::Draw");
		mVAO->Bind();
		glDrawElements(GL_TRIANGLES, mIBO->GetCount(), GL_UNSIGNED_INT, nullptr);

		VertexArray::UnBind();

		Texture::ActiveTexture0();
	}
}
