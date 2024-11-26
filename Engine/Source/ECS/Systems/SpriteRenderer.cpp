#include "SpriteRenderer.h"

#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"
#include "ECS/Components/SpriteAnimator.h"
#include "Logger.h"
#include "Renderer/Renderer.h"
#include "ServiceLocator.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>
#include <nlohmann/json.hpp>

#include <fstream>
#include <vector>

#define NUM_OF_VERTS 6
#define UBO_INDEX 0

SpriteRenderer::SpriteRenderer(unsigned int maxNumSprites) :
	_maxNumSprites(maxNumSprites) {
	ServiceLocator::SetSpriteRenderer(this);
}

void SpriteRenderer::Start() {
	auto camera = _registry->view<Camera2D>().front();
	_camera = &_registry->get<Camera2D>(camera);
}

void SpriteRenderer::Update(float delta) {
	auto view = _registry->view<Transform, Sprite>();

	_sprites.clear();
	unsigned int curNumSprites = 0;


	for (auto [entity, transform, sprite] : view.each()) {
		_sprites.emplace_back(
			GetTexCoords(sprite),
			GetTransform(transform)
		);

		curNumSprites++;

		if (auto animator = _registry->try_get<SpriteAnimator>(entity)) {
			if (!animator->isPlaying || animator->animations.empty()) {
				Logger::Print("No animator");
				continue;
			}

			animator->frameTimer += delta * animator->speed;
			if (animator->frameTimer > 1.0f) {
				animator->frameTimer = 0.0f;
				if (++animator->curFrame == animator->curAnimation->size()) {
					if (animator->isLooping == true) {
						animator->curFrame = 0;
					} else {
						animator->isPlaying = false;
					}
				}
				sprite = Sprite((*animator->curAnimation)[animator->curFrame]);
			}
		}
	}

	if (curNumSprites == 0) {
		return;
	}
	
	_texture.Use();
	_shader.Use();

	GLint uniformLoc = glGetUniformLocation(_shader.GetID(), "CameraMatrix");
	glm::mat3x3 camMat = GetCameraMatrix();
	glUniformMatrix3fv(uniformLoc, 1, GL_FALSE, &camMat[0][0]);

	glBindVertexArray(_vao);

	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_INDEX, _quadInfoUbo);
	glBufferSubData(GL_UNIFORM_BUFFER, UBO_INDEX, _sprites.size() * sizeof(SpriteData), &_sprites[0]);

	// Drawcall
	glDrawArrays(GL_TRIANGLES, 0, curNumSprites * NUM_OF_VERTS);
}

void SpriteRenderer::SetCamera(Camera2D* camera) {
	_camera = camera;
}

void SpriteRenderer::LoadSpriteAtlas(const std::string& imagePath, const std::string& jsonPath) {
	_texture.Load(imagePath.c_str());
	std::ifstream jsonFile(jsonPath);
	nlohmann::json jsonData = nlohmann::json::parse(jsonFile);

	nlohmann::json frames = jsonData.at("frames");
	for (auto& frame : frames) {
		_spriteAtlasFrames.try_emplace(
			frame.at("name").get<std::string>(),
			glm::vec2(frame.at("frame").at("x"), frame.at("frame").at("y")),
			glm::vec2(frame.at("frame").at("w"), frame.at("frame").at("h"))
		);
	}

	nlohmann::json anims = jsonData.at("animations");
	for (auto& anim : anims) {
		Logger::Print("Anim: {}", anim.at("name").get<std::string>());

		glm::vec2 animWidthHeight = glm::vec2(anim.at("size").at("w"), anim.at("size").at("h"));
		auto animFrames = anim.at("frames");
		std::vector<SpriteAtlasData> animFramesData;

		for (auto& animFrame : animFrames) {
			animFramesData.emplace_back(SpriteAtlasData(
				glm::vec2(animFrame.at("x"), animFrame.at("y")),
				animWidthHeight
			));
		}
		
		_spriteAtlasAnims.try_emplace(
			anim.at("name").get<std::string>(),
			animFramesData
		);
	}

	float texSize = jsonData.at("meta").at("size");
	_shader.Use();
	GLint uniformLoc = glGetUniformLocation(_shader.GetID(), "TexSize");
	glUniform1f(uniformLoc, texSize);
}

SpriteRenderer::SpriteAtlasData SpriteRenderer::GetSprite(const std::string& name) {
	return _spriteAtlasFrames.at(name);
}

std::vector<SpriteRenderer::SpriteAtlasData> SpriteRenderer::GetSpriteAnim(const std::string& name) {
	return _spriteAtlasAnims.at(name);
}

void SpriteRenderer::Init(entt::registry* registry) {
	System::Init(registry);

	// If using another rendering system without alpha blending, this
	// would have to be moved into the update function.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	_shader.Load("Engine/Assets/Shaders/Sprite.vert", "Engine/Assets/Shaders/Sprite.frag");
	_texture.Load("Assets/atlas.png");

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

	#pragma region QuadInfoBuffer

	glGenBuffers(1, &_quadInfoUbo);
	glBindBufferBase(GL_UNIFORM_BUFFER, UBO_INDEX, _quadInfoUbo);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(SpriteData) * _maxNumSprites, NULL, GL_DYNAMIC_DRAW);

	_sprites.reserve(_maxNumSprites);

	#pragma endregion QuadInfoBuffer

	// TODO: This is a temporary hardcoded solution
	LoadSpriteAtlas("Assets/atlas.png", "Assets/atlas.json");

	_shader.Use();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}

glm::mat3x3 SpriteRenderer::GetCameraMatrix() {
	glm::mat3x3 identityMat = glm::mat3x3(1.0f);

	if (_camera) {
		return glm::translate(glm::scale(identityMat,
			glm::vec2(_camera->zoom, _camera->zoom)),
			-_camera->position);
	} else {
		return identityMat;
	}

}

glm::mat3x3 SpriteRenderer::GetTransform(Transform transform) {
	glm::mat3x3 translationMatrix = glm::translate(glm::mat3x3(1.0f), transform.position);
	glm::mat3x3 rotationMatrix = glm::rotate(glm::mat3x3(1.0f), transform.rotation);
	glm::mat3x3 scaleMatrix = glm::scale(glm::mat3x3(1.0f), transform.scale);

	return translationMatrix * rotationMatrix * scaleMatrix;
}

glm::vec4 SpriteRenderer::GetTexCoords(Sprite sprite) {
	glm::vec4 texCoords{ sprite.texBaseCoords, sprite.texWidthHeight };

	if (sprite.flip.x) {
		texCoords.x += texCoords.z;
		texCoords.z *= -1;
	}
	if (sprite.flip.y) {
		texCoords.y += texCoords.w;
		texCoords.w *= -1;
	}

	return texCoords;
}