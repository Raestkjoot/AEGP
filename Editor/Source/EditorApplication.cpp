#include "EditorApplication.h"

#include "Logger.h"
#include "ECS/Scene.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Systems/ClearUI.h"
#include "ECS/Systems/UIRenderer.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"

#include <memory>

EditorApplication::EditorApplication() : Application(512, 512, "Hello") { }

void EditorApplication::Initialize() {
	Logger::Print("Hello, Editor!");
	_curScene = new Scene();

	_curScene->AddSystem(std::make_unique<ClearRenderer>());
	_curScene->AddSystem(std::make_unique<ClearUI>());
	std::unique_ptr spriteRenderer = std::make_unique<SpriteRenderer>();
	spriteRenderer->LoadSpriteAtlas("Engine/Assets/DefaultTextures.png", "Engine/Assets/DefaultTextures.json");

	// Prop
	auto entity = _curScene->CreateEntity();
	_curScene->AddComponent<Transform>(entity, glm::vec2(0.0f, 0.0f));
	_curScene->AddComponent<Sprite>(entity, spriteRenderer->GetSprite("DefaultCircle.png"));

	// Camera
	entity = _curScene->CreateEntity();
	_curScene->AddComponent<Camera2D>(entity);
	spriteRenderer->SetCamera(_curScene->GetComponent<Camera2D>(entity));

	_curScene->AddSystem(std::move(spriteRenderer));
	_curScene->AddSystem(std::make_unique<UIRenderer>());

	Application::Initialize();
}