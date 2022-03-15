/* Copyright (C) 2022 Shayan Zamiri <shayan.zamiri@gmail.com> - All Rights Reserved
 * You may use, distribute and modify this code under the terms of the MIT license.
 * You should have received a copy of the MIT license with this file. */

#include "CEPCH.h"
#include "Shader.h"

namespace CE
{
	// STATICS

	void Shader::UnBind()
	{
		glUseProgram(0);
	}

	// CTOR/DTOR & VIRTUAL FUNCTIONS

	Shader::Shader(const std::string& pVertexShader, const std::string& pFragmentShader) :
		mVertexShaderPath{pVertexShader},
		mFragmentShaderPath{pFragmentShader},
		mVertexShader{glCreateShader(GL_VERTEX_SHADER)},
		mFragmentShader{glCreateShader(GL_FRAGMENT_SHADER)},
		mShaderProgram{glCreateProgram()}
	{
		const char* VS = pVertexShader.c_str();
		const char* FS = pFragmentShader.c_str();

		glShaderSource(mVertexShader, 1, &VS, nullptr);
		glShaderSource(mFragmentShader, 1, &FS, nullptr);
	}

	Shader::~Shader()
	{
		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);
		glDeleteProgram(mShaderProgram);
	}

	// FUNCTIONS

	void Shader::Compile() const
	{
		glCompileShader(mVertexShader);
		glCompileShader(mFragmentShader);

		// Check errors
		GLint VSResult;
		GLint FSResult;
		glGetShaderiv(mVertexShader, GL_COMPILE_STATUS, &VSResult);
		glGetShaderiv(mFragmentShader, GL_COMPILE_STATUS, &FSResult);
		spdlog::info("Vertex shader compile status: {}", VSResult);
		spdlog::info("Fragment shader compile status: {}", FSResult);

		//TODO: Implement error handler function
		if (VSResult != GL_TRUE)
		{
			GLsizei Length;
			glGetShaderiv(VSResult, GL_INFO_LOG_LENGTH, &Length);
			// alloca(): allocate memory in this function stack
			GLchar* Message = static_cast<char*>(alloca(Length * sizeof(GLchar)));
			glGetShaderInfoLog(VSResult, Length, &Length, Message);
			spdlog::error("Failed to compile Vertex Shader: {}", Message);
			glDeleteShader(VSResult);
		}

		if (FSResult != GL_TRUE)
		{
			GLsizei Length;
			glGetShaderiv(FSResult, GL_INFO_LOG_LENGTH, &Length);
			GLchar* Message = static_cast<char*>(alloca(Length * sizeof(GLchar)));
			glGetShaderInfoLog(FSResult, Length, &Length, Message);
			spdlog::error("Failed to compile Fragment Shader: {}", Message);
			glDeleteShader(FSResult);
		}
	}

	void Shader::Link() const
	{
		glAttachShader(mShaderProgram, mFragmentShader);
		glAttachShader(mShaderProgram, mVertexShader);
		glLinkProgram(mShaderProgram);

		// Check errors
		GLint Result;
		glGetProgramiv(mShaderProgram, GL_LINK_STATUS, &Result);
		spdlog::info("Program link status: {}", Result);
		if (Result != GL_TRUE)
		{
			GLsizei Length;
			glGetProgramiv(Result, GL_INFO_LOG_LENGTH, &Length);
			GLchar* Message = static_cast<char*>(alloca(Length * sizeof(GLchar)));
			glGetProgramInfoLog(mShaderProgram, Length, &Length, Message);
			spdlog::error("Failed to link program: {}", Message);
			glDeleteProgram(mShaderProgram);
		}

		glValidateProgram(mShaderProgram);

		glDeleteShader(mVertexShader);
		glDeleteShader(mFragmentShader);
	}

	void Shader::Bind() const
	{
		glUseProgram(mShaderProgram);
	}

	GLint Shader::GetUniformLocation(const std::string& pName) const
	{
		const GLint Location = glGetUniformLocation(mShaderProgram, pName.c_str());
		if (Location == -1)
			spdlog::error("No active uniform variable with name {} found", pName);

		return Location;
	}

	void Shader::SetUniform1i(const std::string& pName, GLint pValue) const
	{
		glUniform1i(GetUniformLocation(pName), pValue);
	}

	void Shader::SetUniform1f(const std::string& pName, GLfloat pValue) const
	{
		glUniform1f(GetUniformLocation(pName), pValue);
	}

	void Shader::SetUniform4f(const std::string& pName, GLfloat pF0, GLfloat pF1, GLfloat pF2, GLfloat pF3) const
	{
		glUniform4f(GetUniformLocation(pName), pF0, pF1, pF2, pF3);
	}

	void Shader::SetUniformMat4f(const std::string& pName, const glm::mat4& pMatrix) const
	{
		glUniformMatrix4fv(GetUniformLocation(pName), 1,GL_FALSE, &pMatrix[0][0]);
	}
}
