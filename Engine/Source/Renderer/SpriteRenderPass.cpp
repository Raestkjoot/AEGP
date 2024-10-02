#include "SpriteRenderPass.h"

#include "Renderer.h"
#include "Logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <vector>

#define NUM_OF_VERTS 6
#define NUM_OF_INFO_VARS 3

SpriteRenderPass::SpriteRenderPass(unsigned int maxNumSprites) 
	: _maxNumSprites(maxNumSprites) { }

void SpriteRenderPass::Init() {
	_shader.Load("Engine/Assets/Shaders/Sprite.vert", "Engine/Assets/Shaders/Sprite.frag");

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
	vertices.reserve(_maxNumSprites * NUM_OF_VERTS);

	for (unsigned int quadIter = 0; quadIter < _maxNumSprites; ++quadIter) {
		for (unsigned int vertIter = 0; vertIter < NUM_OF_VERTS; ++vertIter) {
			vertices.emplace_back(
				quadVertexPositions[vertIter],
				quadIter
			);
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

	#pragma region Texture

	glGenTextures(1, &_texture);
	glBindTexture(GL_TEXTURE_2D, _texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
	// set the texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load image, create texture and generate mipmaps
	int width, height, nrChannels;
	unsigned char* data = stbi_load("Engine/Assets/DefaultTextures.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		Logger::PrintError("Failed to load texture");
	}
	stbi_image_free(data);

	#pragma endregion Texture

	#pragma region QuadInfoBuffer
	
	GLuint blockIndex = glGetUniformBlockIndex(_shader.GetID(), "QuadInfo");
	glUniformBlockBinding(_shader.GetID(), 0, blockIndex);
	glGetActiveUniformBlockiv(_shader.GetID(), blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &static_cast<GLint>(_blockSize));

	_quadInfoBuffer = (GLubyte*)malloc(_blockSize);

	const GLchar* names[] = {
		"Transform",
		"TexCoords",
		"TexWidthHeight"
	};
	GLuint indices[NUM_OF_INFO_VARS] = { 0 };
	glGetUniformIndices(_shader.GetID(), NUM_OF_INFO_VARS, names, indices);

	GLint offsets[NUM_OF_INFO_VARS];
	glGetActiveUniformsiv(_shader.GetID(), NUM_OF_INFO_VARS, indices, GL_UNIFORM_OFFSET, offsets);

	_quadInfoOffsets.transform = offsets[0];
	_quadInfoOffsets.texCoords = offsets[1];
	_quadInfoOffsets.texWidthHeight = offsets[2];

	glGenBuffers(1, &_uniformBuffer);

	#pragma endregion QuadIDBuffer
}

void SpriteRenderPass::Render() {
	glBindTexture(GL_TEXTURE_2D, _texture);
	_shader.Use();
	glBindVertexArray(_vao);

	glBindBuffer(GL_UNIFORM_BUFFER, _uniformBuffer);
	glBufferData(GL_UNIFORM_BUFFER, _blockSize, _quadInfoBuffer, GL_DYNAMIC_DRAW);
	glBindBufferBase(GL_UNIFORM_BUFFER, 0, _uniformBuffer);

	// Drawcall
	glDrawArrays(GL_TRIANGLES, 0, _curNumSprites * NUM_OF_VERTS);
}

unsigned int SpriteRenderPass::AddSprite() {
	return _curNumSprites++;
}