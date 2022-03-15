/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#pragma once

#include "CETypes.h"
#include "glm/glm.hpp"
#include "glad/glad.h"

namespace CE
{
	class Shader
	{
		// CTOR/DTOR & VIRTUAL FUNCTIONS
	public:
		Shader(const std::string& pVertexShader, const std::string& pFragmentShader);

		virtual ~Shader();

		// FUNCTIONS
	public:
		static void UnBind();

		void Compile() const;

		void Link() const;

		void Bind() const;

		GLint GetUniformLocation(const std::string& pName) const;

		void SetUniform1i(const std::string& pName, GLint pValue) const;

		void SetUniform1f(const std::string& pName, GLfloat pValue) const;

		void SetUniform4f(const std::string& pName, GLfloat pF0, GLfloat pF1, GLfloat pF2, GLfloat pF3) const;

		void SetUniformMat4f(const std::string& pName, const glm::mat4& pMatrix) const;

		// PROPERTIES
	public:
		std::string mVertexShaderPath;
		std::string mFragmentShaderPath;
		const GLuint mVertexShader;
		const GLuint mFragmentShader;
		const GLuint mShaderProgram;
	};
}
