#include "Transform.h"
#include "Transform.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/matrix_transform_2d.hpp>

glm::vec2 Transform::GetPosition() const {
	return _position;
}

float Transform::GetRotation() const {
	return _rotation;
}

float Transform::GetScale() const {
	return _scale;
}

void Transform::SetPosition(glm::vec2 position) {
	_position = position;
	_dirty = true;
}

void Transform::SetRotation(float rotation) {
	_rotation = rotation;
	_dirty = true;
}

void Transform::SetScale(float scale) {
	_scale = scale;
	_dirty = true;
}

glm::mat3x3 Transform::GetTransform() {
	glm::mat3x3 trans = glm::translate(glm::mat3x3(1.0f), _position)
		* glm::rotate(glm::mat3x3(1.0f), glm::radians(_rotation))
		* glm::scale(glm::mat3x3(1.0f), {_scale, _scale});

	//trans = glm::rotate(trans, glm::radians(_rotation));
	//trans = glm::scale(trans, glm::scale(_scale));

	return trans;
}