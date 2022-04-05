/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "Texture.h"
#include "FileManager.h"

namespace CE
{
	// STATICS

	void Texture::UnBind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void Texture::ActiveTexture0()
	{
		glActiveTexture(GL_TEXTURE0);
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	Texture::Texture() : mID{0}, mFormat{0}, mType{ETextureType::NONE}, mWidth{0}, mHeight{0}
	{
		glGenTextures(1, &mID);
	}

	Texture::~Texture()
	{
		glDeleteTextures(1, &mID);
	}

	void Texture::Bind() const
	{
		glBindTexture(GL_TEXTURE_2D, mID);
	}

	// FUNCTIONS

	bool Texture::LoadTexture(const std::string& pFilePath)
	{
		GLint channels = 0;
		if (GLubyte* textureData = FileManager::LoadImage(pFilePath, mWidth, mHeight, channels))
		{
			if (channels == 1)
				mFormat = GL_RED;
			else if (channels == 3)
				mFormat = GL_RGB;
			else if (channels == 4)
				mFormat = GL_RGBA;

			Bind();
			glTexImage2D(GL_TEXTURE_2D, 0, mFormat, mWidth, mHeight, 0, mFormat, GL_UNSIGNED_BYTE, textureData);
			glGenerateMipmap(GL_TEXTURE_2D);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			free(textureData);

			mFilePath = pFilePath;
			return true;
		}
		else
		{
			spdlog::error("Texture failed to load at path: {}", pFilePath);
			free(textureData);
			return false;
		}
	}
}
