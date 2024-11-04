#include "EditorScene.h"

#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Systems/ClearUI.h"
#include "ECS/Systems/UIRenderer.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"

#include <memory>

void EditorScene::Initialize() {
	AddSystem(std::make_unique<ClearRenderer>());
	AddSystem(std::make_unique<ClearUI>());
	std::unique_ptr spriteRenderer = std::make_unique<SpriteRenderer>();
	spriteRenderer->LoadSpriteAtlas("Engine/Assets/DefaultTextures.png", "Engine/Assets/DefaultTextures.json");

	// Prop
	auto entity = CreateEntity();
	AddComponent<Transform>(entity, glm::vec2(0.0f, 0.0f));
	AddComponent<Sprite>(entity, spriteRenderer->GetSprite("DefaultCircle.png"));

	// Camera
	entity = CreateEntity();
	AddComponent<Camera2D>(entity);
	spriteRenderer->SetCamera(GetComponent<Camera2D>(entity));

	AddSystem(std::move(spriteRenderer));
	AddSystem(std::make_unique<UIRenderer>());
}