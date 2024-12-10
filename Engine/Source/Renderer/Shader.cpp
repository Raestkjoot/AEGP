#include "Shader.h"

#include "Utils/Logger.h"
#include "Renderer.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

void Shader::Load(const char* vertexPath, const char* fragmentPath) {
	std::string vertexCode, fragmentCode;
	std::ifstream vShaderFile, fShaderFile;

	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try {
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);

		std::stringstream vShaderStream, fShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		vShaderFile.close();
		fShaderFile.close();
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	} catch (std::ifstream::failure e) {
		Logger::PrintError("ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ");
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	// Compile shaders
	unsigned int vertex, fragment;
	int success;
	char infoLog[512];

	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n   {}", infoLog);
	}

	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n   {}", infoLog);
	}

	_id = glCreateProgram();
	glAttachShader(_id, vertex);
	glAttachShader(_id, fragment);
	glLinkProgram(_id);
	glGetProgramiv(_id, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_id, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER::PROGRAM::LINKING_FAILED\n   {}", infoLog);
	}

	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use() {
	glUseProgram(_id);
}

unsigned int Shader::GetID() const {
	return _id;
}