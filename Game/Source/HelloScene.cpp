#include "HelloScene.h"

#include "HelloSystem.h"
#include "MoveSystem.h"
#include "PlayerControllerTag.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"

void HelloScene::Initialize() {
	AddSystem(std::make_unique<HelloSystem>());
	AddSystem(std::make_unique<MoveSystem>());
	AddSystem(std::make_unique<ClearRenderer>());
	std::unique_ptr spriteRenderer = std::make_unique<SpriteRenderer>();
	spriteRenderer->LoadSpriteAtlas("Engine/Assets/DefaultTextures.png", "Engine/Assets/DefaultTextures.json");

	// Player
	auto entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(-0.5f, -0.5f));
	AddComponent<Sprite>(entity, spriteRenderer->GetSprite("DefaultCircle.png"));
	AddComponent<PlayerControllerTag>(entity);

	// Prop
	entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(-0.45f, -0.45f));
	Sprite testSprite{ spriteRenderer->GetSprite("DefaultOutlineSquare.png") };
	testSprite.flip.x = true;
	testSprite.flip.y = true;
	AddComponent<Sprite>(entity, testSprite);

	// Camera
	entity = CreateEntity();
	AddComponent<Camera2D>(entity);
	spriteRenderer->SetCamera(GetComponent<Camera2D>(entity));

	AddSystem(std::move(spriteRenderer));
}