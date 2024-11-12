#include "CameraFollowSystem.h"

#include "ECS/Components/Camera2D.h"
#include "PlayerControllerTag.h"
#include "ECS/Components/Transform.h"

void CameraFollowSystem::Update(float delta) {
	auto playerView = _registry->view<Transform, PlayerControllerTag>();
	auto cameraView = _registry->view<Camera2D>();

	auto player = playerView.front();
	auto camera = cameraView.front();

	auto& playerTransform = _registry->get<Transform>(player);

	auto& cameraCamera = _registry->get<Camera2D>(camera);
	cameraCamera.position = playerTransform.position;
}
