#include "HelloApplication.h"

#include "Logger.h"
#include "SceneLoader.h"

// Systems
#include "SystemFactory.h"
#include "HelloSystem.h"
#include "MoveSystem.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/ClearUI.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Systems/UIRenderer.h"

// Components
#include "ComponentFactory.h"
#include "PlayerControllerTag.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Camera2D.h"

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include "nlohmann/json.hpp"

HelloApplication::HelloApplication() : Application(512, 512, "Hello") { }

void HelloApplication::Initialize() {
	Logger::Print("App: Hello, world!");
	
	_systemFactory->RegisterSystem("HelloSystem", []() {return std::make_unique<HelloSystem>(); });
	_systemFactory->RegisterSystem("MoveSystem", []() {return std::make_unique<MoveSystem>(); });
	_systemFactory->RegisterSystem("ClearRenderer", []() {return std::make_unique<ClearRenderer>(); });
	_systemFactory->RegisterSystem("ClearUI", []() {return std::make_unique<ClearUI>(); });
	_systemFactory->RegisterSystem("SpriteRenderer", []() {return std::make_unique<SpriteRenderer>(); });
	_systemFactory->RegisterSystem("UIRenderer", []() {return std::make_unique<UIRenderer>(); });

	_componentFactory->RegisterComponent("Transform", [](Scene* scene, entt::entity e, nlohmann::json& args) {
		scene->AddComponent<Transform>(e, args);
	});
	_componentFactory->RegisterComponent("Sprite", [](Scene* scene, entt::entity e, nlohmann::json& args) {
		scene->AddComponent<Sprite>(e, args);
	});
	_componentFactory->RegisterComponent("Camera2D", [](Scene* scene, entt::entity e, nlohmann::json& args) { scene->AddComponent<Camera2D>(e); });
	_componentFactory->RegisterComponent("PlayerControllerTag", [](Scene* scene, entt::entity e, nlohmann::json& args) { scene->AddComponent<PlayerControllerTag>(e); });

	LoadScene("Assets/HelloScene.json");

	Application::Initialize();
}