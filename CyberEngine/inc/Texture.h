/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "glad/glad.h"

namespace CE
{
	class Texture
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		Texture();

		virtual ~Texture();

		// FUNCTIONS
	public:
		static void UnBind();

		static void ActiveTexture0();

		void Bind() const;

		bool LoadTexture(const std::string& pFilePath);

		// GETTERS & SETTERS
	public:
		GLuint GetID() const { return mID; }

		ETextureType GetType() const { return mType; }

		void SetType(ETextureType pType) { mType = pType; }

		std::string_view GetFilePath() const { return mFilePath; }

		// PROPERTIES
	private:
		GLuint mID;
		GLenum mFormat;
		ETextureType mType;
		GLsizei mWidth;
		GLsizei mHeight;
		std::string mFilePath;
	};
}
