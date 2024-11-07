#include "HelloScene.h"

#include "HelloSystem.h"
#include "MoveSystem.h"
#include "PlayerControllerTag.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Systems/ClearUI.h"
#include "ECS/Systems/UIRenderer.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"

void HelloScene::Initialize() {
	AddSystem(std::make_unique<HelloSystem>());
	AddSystem(std::make_unique<MoveSystem>());
	AddSystem(std::make_unique<ClearRenderer>());
	AddSystem(std::make_unique<ClearUI>());
	std::unique_ptr spriteRenderer = std::make_unique<SpriteRenderer>();
	// TODO: Load atlas through SceneLoader
	spriteRenderer->LoadSpriteAtlas("Engine/Assets/DefaultTextures.png", "Engine/Assets/DefaultTextures.json");

	// Player
	auto entity = CreateEntity();
	// TODO: Set transform position through SceneLoader
	AddComponent<Transform>(entity, glm::vec2(0.0f, 0.0f));
	// TODO: Set sprite through SceneLoader
	AddComponent<Sprite>(entity, spriteRenderer->GetSprite("DefaultCircle.png"));
	AddComponent<PlayerControllerTag>(entity);

	// Prop
	entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(-0.05f, -0.05f));
	Sprite testSprite{ spriteRenderer->GetSprite("DefaultOutlineSquare.png") };
	testSprite.flip.x = true;
	testSprite.flip.y = true;
	AddComponent<Sprite>(entity, testSprite);

	// Camera
	entity = CreateEntity();
	AddComponent<Camera2D>(entity);
	// TODO: Set camera through SceneLoader
	spriteRenderer->SetCamera(GetComponent<Camera2D>(entity));

	AddSystem(std::move(spriteRenderer));
	AddSystem(std::make_unique<UIRenderer>());
}