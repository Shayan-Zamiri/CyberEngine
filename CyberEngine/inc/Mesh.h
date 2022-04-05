/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "glad/glad.h"
#include "Texture.h"

namespace CE
{
	class Shader;

	struct Vertex
	{
		glm::vec3 mPosition;
		glm::vec3 mNormal;
		glm::vec2 mTexCoords;
	};

	class Mesh
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		Mesh(Mesh&& pMesh) noexcept;

		Mesh(const std::vector<Vertex>& pVertices, const std::vector<GLuint>& pIndices,
		     std::vector<std::shared_ptr<Texture>> pTextures);

		virtual ~Mesh() = default;

		// FUNCTIONS
	public:
		void SetupMeshData(const std::vector<Vertex>& pVertices, const std::vector<GLuint>& pIndices);

		void SetupTextures(const Shader& pShader);

		void Draw() const;

		// PROPERTIES
	private:
		std::unique_ptr<VertexArray> mVAO;
		std::unique_ptr<VertexBuffer> mVBO;
		std::unique_ptr<IndexBuffer> mIBO;
		std::vector<std::shared_ptr<Texture>> mTextures;
	};
}
