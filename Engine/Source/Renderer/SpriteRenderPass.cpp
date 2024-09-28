#include "SpriteRenderPass.h"

#include "Renderer.h"
#include "Logger.h"

void SpriteRenderPass::Init() {
	#pragma region Shaders
	// vertex shader
	const char* vertexShaderSource = "#version 330 core\n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check fr shader compile errors
	int  success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		Logger::PrintError("ERROR::SHADER::VERTEX::COMPILATION_FAILED\n{}", infoLog);
	}

	// Fragment shader
	const char* fragmentShaderSource = "#version 330 core\n"
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
}

void SpriteRenderPass::Render() {
	glUseProgram(_shaderProgram);

	// VBO
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(_vertices), &_vertices[0], GL_STATIC_DRAW);

	// VAO
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(_vertices), &_vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// EBO
	unsigned int ebo;
	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(_indices), &_indices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);

	// Drawcall
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

int16_t SpriteRenderPass::AddSprite()
{
	_vertices.push_back({ 0.125f, 0.125f, 0.0f }); // top right
	_vertices.push_back({ 0.125f, -0.125f, 0.0f }); // bottom right
	_vertices.push_back({ -0.125f, -0.125f, 0.0f }); // bottom left
	_vertices.push_back({ -0.125f,  0.125f, 0.0f }); // top left 

	// Triangle 1
	_indices.push_back(_curTopIndex + 1);
	_indices.push_back(_curTopIndex + 2);
	_indices.push_back(_curTopIndex + 4);
	// Triangle 2
	_indices.push_back(_curTopIndex + 2);
	_indices.push_back(_curTopIndex + 3);
	_indices.push_back(_curTopIndex += 4);

	return 0;
}