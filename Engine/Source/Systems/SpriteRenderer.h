#pragma once

#include "System.h"
#include "Renderer/Shader.h"
#include "Renderer/Texture.h"
#include "Components/Transform.h"

#include <glm/glm.hpp>

#include <map>

struct Sprite;
struct Camera2D;

class SpriteRenderer : public System {
public:

	SpriteRenderer(unsigned int maxNumSprites = 1000);

	void Start() override;
	void Update(float delta) override;

	void SetCamera(Camera2D* camera);

	struct SpriteAtlasData {
		glm::vec2 texBaseCoords;
		glm::vec2 texWidthHeight;

		SpriteAtlasData(const glm::vec2& texBaseCoords, const glm::vec2& texWidthHeight) :
			texBaseCoords(texBaseCoords),
			texWidthHeight(texWidthHeight) { }
	};
	void LoadSpriteAtlas(const std::string& imagePath, const std::string& jsonPath);
	SpriteAtlasData GetSprite(const std::string& name);
	std::vector<SpriteAtlasData> GetSpriteAnim(const std::string& name);

private:
	void Init(entt::registry* registry) override;

	glm::mat3x3 GetCameraMatrix();

	struct Vertex {
		glm::vec2 position;
		unsigned int quadID;

		Vertex(const glm::vec2& position, unsigned int quadID) :
			position(position),
			quadID(quadID) { }
	};

	struct SpriteData {
		glm::vec4 texCoords;
		glm::mat3x4 transform; // mat3x3, padded for std140

		SpriteData(const glm::vec4& texCoords, const glm::mat3x3& transform) :
			texCoords(texCoords),
			transform(transform) { }
	};

	glm::mat3x3 GetTransform(Transform transform);
	glm::vec4 GetTexCoords(Sprite sprite);

	std::vector<SpriteData> _sprites;
	std::map<std::string, SpriteAtlasData> _spriteAtlasFrames;
	std::map<std::string, std::vector<SpriteAtlasData>> _spriteAtlasAnims;

	Camera2D* _camera = nullptr;
	unsigned int _maxNumSprites;
	unsigned int _vao = 0;
	unsigned int _quadInfoUbo = 0;
	Texture _texture{};
	Shader _shader{};

	// Timings: Querying OpenGL render Times
private:
	unsigned int _queryID[2][1];
	unsigned int _queryBackBuffer = 0, _queryFrontBuffer = 1;

	void GenQueries();
	void SwapQueryBuffers();
};