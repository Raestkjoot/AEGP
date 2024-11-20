#include "PrototypeApplication.h"

#include "Logger.h"
#include "SceneLoader.h"

// Systems
#include "SystemFactory.h"
#include "AudioManagerSystem.h"
#include "MoveSystem.h"
#include "CameraFollowSystem.h"
#include "PlayerCollisionSystem.h"
#include "ECS/Systems/ClearRenderer.h"
#include "ECS/Systems/ClearUI.h"
#include "ECS/Systems/SpriteRenderer.h"
#include "ECS/Systems/UIRenderer.h"

// Components
#include "ComponentFactory.h"
#include "PlayerController.h"
#include "ECS/Components/Transform.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/SpriteAnimator.h"
#include "ECS/Components/Camera2D.h"
#include "ECS/Components/AABB.h"
#include "ECS/Components/Collider_Dynamic.h"
#include "ECS/Components/Collider_Static.h"
#include "ECS/Components/Collider_Trigger.h"

#include <GLFW/glfw3.h>
#include <entt/entt.hpp>
#include "nlohmann/json.hpp"

PrototypeApplication::PrototypeApplication() : Application(512, 512, "Hello") { }

void PrototypeApplication::Initialize() {
	_systemFactory->RegisterSystem("AudioManagerSystem", []() {return std::make_unique<AudioManagerSystem>(); });
	_systemFactory->RegisterSystem("MoveSystem", []() {return std::make_unique<MoveSystem>(); });
	_systemFactory->RegisterSystem("CameraFollowSystem", []() {return std::make_unique<CameraFollowSystem>(); });
	_systemFactory->RegisterSystem("ClearRenderer", []() {return std::make_unique<ClearRenderer>(); });
	_systemFactory->RegisterSystem("ClearUI", []() {return std::make_unique<ClearUI>(); });
	_systemFactory->RegisterSystem("SpriteRenderer", []() {return std::make_unique<SpriteRenderer>(); });
	_systemFactory->RegisterSystem("UIRenderer", []() {return std::make_unique<UIRenderer>(); });
	_systemFactory->RegisterSystem("PlayerCollisionSystem", []() {return std::make_unique<PlayerCollisionSystem>(); });

	_componentFactory->RegisterComponent("Transform", [](Scene* scene, entt::entity e, nlohmann::json& args) 
		{ scene->AddComponent<Transform>(e, args);});
	_componentFactory->RegisterComponent("Sprite", [](Scene* scene, entt::entity e, nlohmann::json& args) 
		{ scene->AddComponent<Sprite>(e, args); });
	_componentFactory->RegisterComponent("Camera2D", [](Scene* scene, entt::entity e, nlohmann::json& args) 
		{ scene->AddComponent<Camera2D>(e); });
	_componentFactory->RegisterComponent("PlayerController", [](Scene* scene, entt::entity e, nlohmann::json& args) 
		{ scene->AddComponent<PlayerController>(e); });
	_componentFactory->RegisterComponent("AABB", [](Scene* scene, entt::entity e, nlohmann::json& args) 
		{ scene->AddComponent<AABB>(e, args); });
	_componentFactory->RegisterComponent("Collider_Dynamic", [](Scene* scene, entt::entity e, nlohmann::json& args)
		{ scene->AddComponent<Collider_Dynamic>(e); });
	_componentFactory->RegisterComponent("Collider_Static", [](Scene* scene, entt::entity e, nlohmann::json& args)
		{ scene->AddComponent<Collider_Static>(e); });
	_componentFactory->RegisterComponent("Collider_Trigger", [](Scene* scene, entt::entity e, nlohmann::json& args)
		{ scene->AddComponent<Collider_Trigger>(e); });
	_componentFactory->RegisterComponent("SpriteAnimator", [](Scene* scene, entt::entity e, nlohmann::json& args)
		{ scene->AddComponent<SpriteAnimator>(e); });

	LoadScene("Assets/PrototypeScene.json");

	Application::Initialize();
}