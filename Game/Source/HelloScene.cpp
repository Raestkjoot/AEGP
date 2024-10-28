#include "HelloScene.h"

#include "HelloSystem.h"
#include "MoveSystem.h"
#include "PlayerControllerTag.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"

void HelloScene::Initialize() {
	AddSystem(std::make_unique<HelloSystem>());
	AddSystem(std::make_unique<MoveSystem>());
	AddSystem(std::make_unique<ClearRenderer>());
	std::unique_ptr spriteRenderer = std::make_unique<SpriteRenderer>();
	spriteRenderer->LoadSpriteAtlas("Engine/Assets/DefaultTextures.png", "Engine/Assets/DefaultTextures.json");

	auto entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(-0.5f, -0.5f));
	AddComponent<Sprite>(entity, spriteRenderer->GetSprite("DefaultSquare.png"));
	AddComponent<PlayerControllerTag>(entity);
	entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(-0.45f, -0.45f));
	AddComponent<Sprite>(entity, spriteRenderer->GetSprite("DefaultOutlineSquare.png"));

	AddSystem(std::move(spriteRenderer));
}