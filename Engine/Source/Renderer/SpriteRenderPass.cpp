#include "SpriteRenderPass.h"
#include "SpriteRenderPass.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

#include "Renderer.h"
#include "Logger.h"

#define NUM_OF_VERTS 6

SpriteRenderPass::SpriteRenderPass(unsigned int maxNumSprites) 
	: _maxNumSprites(maxNumSprites) { }

void SpriteRenderPass::Init() {
	#pragma region Shaders
	// vertex shader
	const char* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 0) in vec2 Pos;\n"
		"layout (location = 1) in uint QuadID;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(Pos, 0.5, 1.0);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check frag shader compile errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
	}

	// Fragment shader
	const char* fragmentShaderSource = 
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
		"}\n\0";
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n{}", infoLog);
	}

	// Compile and use shader program
	_shaderProgram = glCreateProgram();
	glAttachShader(_shaderProgram, vertexShader);
	glAttachShader(_shaderProgram, fragmentShader);
	glLinkProgram(_shaderProgram);
	glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(_shaderProgram, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER_PROGRAM::LINKING_FAILED\n{}", infoLog);
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	#pragma endregion Shaders

	#pragma region VertexArray
	// Generate vertices for the max number of quads
	glm::vec2 quadVertexPositions[] = {
		glm::vec2(0.0f, 0.0f), // bottom left
		glm::vec2(0.0f, 1.0f), // top left
		glm::vec2(1.0f, 1.0f), // top right
		glm::vec2(0.0f, 0.0f), // bottom left
		glm::vec2(1.0f, 1.0f), // top right
		glm::vec2(1.0f, 0.0f)  // bottom right
	};

	std::vector<Vertex> vertices;
	vertices.resize(_maxNumSprites * NUM_OF_VERTS);

	for (unsigned int quadIter = 0; quadIter < _maxNumSprites; ++quadIter) {
		for (unsigned int vertIter = 0; vertIter < NUM_OF_VERTS; ++vertIter) {
			vertices[quadIter * NUM_OF_VERTS + vertIter].position = quadVertexPositions[vertIter];
			vertices[quadIter * NUM_OF_VERTS + vertIter].quadID = quadIter;
		}
	}


	// Bind buffers
	glGenVertexArrays(1, &_vao);
	glBindVertexArray(_vao);
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	// Add data
	unsigned int size = vertices.size() * sizeof(Vertex);
	glBufferData(GL_ARRAY_BUFFER, size, &vertices[0], GL_STATIC_DRAW);
	// Position attribute (location = 0)
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
	glEnableVertexAttribArray(0);
	// QuadID attribute (location = 1)
	glVertexAttribIPointer(1, 1, GL_UNSIGNED_INT, sizeof(Vertex), (void*)offsetof(Vertex, quadID));
	glEnableVertexAttribArray(1);

	// Unbind buffers
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	#pragma endregion VertexArray

	#pragma region QuadInfoBuffer
	
	// TODO

	#pragma endregion QuadIDBuffer
}

void SpriteRenderPass::Render() {
	glUseProgram(_shaderProgram);
	glBindVertexArray(_vao);

	// Drawcall
	glDrawArrays(GL_TRIANGLES, 0, _curNumSprites * NUM_OF_VERTS);
}

unsigned int SpriteRenderPass::AddSprite() {
	return _curNumSprites += 10;
}