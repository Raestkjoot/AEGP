#pragma once

#include "ECS/System.h"
#include "Renderer/Shader.h"
#include "ECS/Components/Transform.h"

#include <glm/glm.hpp>

class SpriteRenderer : public System {
public:
	SpriteRenderer(unsigned int maxNumSprites = 1000);

	void Start() override;
	void Update(float delta) override;
	void End() override;

private:
	void Init(entt::registry* registry) override;

	struct Vertex {
		glm::vec2 position;
		unsigned int quadID;

		Vertex(const glm::vec2& position, unsigned int quadID) :
			position(position),
			quadID(quadID) { }
	};

	struct SpriteData {
		glm::vec2 texWidthHeight;
		glm::vec2 texBaseCoords;
		glm::mat3x4 transform; // mat3x3, padded for std140

		SpriteData(const glm::vec2& texWidthHeight, const glm::vec2& texBaseCoords, const glm::mat3x3& transform) :
			texWidthHeight(texWidthHeight),
			texBaseCoords(texBaseCoords),
			transform(transform) { }
	};

	glm::mat3x4 GetTransform(Transform transform);

	std::vector<SpriteData> _sprites;

	unsigned int _maxNumSprites;
	unsigned int _vao = 0;
	unsigned int _texture = 0;
	unsigned int _quadInfoUbo = 0;
	Shader _shader{};
};