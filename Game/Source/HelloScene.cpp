#include "HelloScene.h"

#include "HelloSystem.h"
#include "MoveSystem.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"

void HelloScene::Initialize() {
	AddSystem(std::make_unique<HelloSystem>());
	AddSystem(std::make_unique<MoveSystem>());
	AddSystem(std::make_unique<ClearRenderer>());
	AddSystem(std::make_unique<SpriteRenderer>());

	auto entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(-0.5f, -0.5f));
	AddComponent<Sprite>(entity);
}