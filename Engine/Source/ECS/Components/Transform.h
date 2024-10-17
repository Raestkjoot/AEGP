#pragma once

#include <glm/glm.hpp>
#include <entt/entt.hpp>

class Transform {
	friend class UpdateSpriteTransforms;
public:
	glm::vec2 GetPosition() const;
	float GetRotation() const;
	float GetScale() const;

	void SetPosition(glm::vec2 position);
	void SetRotation(float rotation);
	void SetScale(float scale);

	glm::mat3x3 GetTransform();

private:
	glm::vec2 _position{};
	float _rotation{};
	float _scale{};
	bool _dirty = false;
};