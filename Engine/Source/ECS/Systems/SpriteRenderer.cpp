#include "SpriteRenderer.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "Logger.h"
#include "Renderer/Renderer.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

#include <vector>

#define NUM_OF_VERTS 6
#define UBO_INDEX 0

SpriteRenderer::SpriteRenderer(unsigned int maxNumSprites) {
	_maxNumSprites = maxNumSprites;
}

void SpriteRenderer::Start() {

}

void SpriteRenderer::Update() {
	auto view = _registry->view<Transform, Sprite>();

	unsigned int curNumSprites = 0;

	for (auto [entity, transform, sprite] : view.each()) {
		// TODO: Use GetTransform(transform);
		//Logger::Print("Rendering sprite at position {}, {}", transform.position.x, transform.position.y);

		glm::mat3x3 trans = glm::translate(glm::mat3x3(1.0f), glm::vec2(-0.5f, -0.5f));
		_sprites.emplace_back(
			sprite.texWidthHeight,
			sprite.texBaseCoords,
			trans //GetTransform(transform)
		);

		curNumSprites++;
	}

	if (curNumSprites == 0) {
		return;
	}

	glBindTexture(GL_TEXTURE_2D, _texture);
	_shader.Use();
	glBindVertexArray(_vao);

	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_INDEX, _quadInfoUbo);
	glBufferSubData(GL_UNIFORM_BUFFER, UBO_INDEX, _sprites.size() * sizeof(SpriteData), &_sprites[0]);

	// Drawcall
	glDrawArrays(GL_TRIANGLES, 0, curNumSprites * NUM_OF_VERTS);
}

void SpriteRenderer::End() {

}

void SpriteRenderer::Init(entt::registry* registry) {
	System::Init(registry);

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
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("Engine/Assets/DefaultTextures.png", &width, &height, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		Logger::PrintError("Failed to load texture");
	}
	stbi_image_free(data);

	#pragma endregion Texture

	#pragma region QuadInfoBuffer

	glGenBuffers(1, &_quadInfoUbo);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_INDEX, _quadInfoUbo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SpriteData) * _maxNumSprites, NULL, GL_DYNAMIC_DRAW);

	_sprites.reserve(_maxNumSprites);

	#pragma endregion QuadInfoBuffer
}

glm::mat3x4 SpriteRenderer::GetTransform(Transform transform) {
	return glm::translate(glm::mat3x3(1.0f), transform.position)
			* glm::rotate(glm::mat3x3(1.0f), glm::radians(transform.rotation))
			* glm::scale(glm::mat3x3(1.0f), transform.scale);
}
