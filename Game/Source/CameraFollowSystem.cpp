#include "CameraFollowSystem.h"

#include "Components/Camera2D.h"
#include "Components/Transform.h"
#include "PlayerController.h"

void CameraFollowSystem::Update(float delta) {
	auto playerView = _registry->view<Transform, PlayerController>();
	auto cameraView = _registry->view<Camera2D>();

	auto player = playerView.front();
	auto camera = cameraView.front();

	auto& playerTransform = _registry->get<Transform>(player);

	auto& cameraCamera = _registry->get<Camera2D>(camera);
	cameraCamera.position = playerTransform.position;
}
