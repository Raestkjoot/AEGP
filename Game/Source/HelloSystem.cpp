#include "HelloSystem.h"

#include "Logger.h"
#include "ECS/Components/Transform.h"

void HelloSystem::Start() {
	// This is the way to get all entities
	// TODO: Might want to make our own function for this too?
	//for (auto entity : _registry->view<entt::entity>()) {
	//	Logger::Print("Entt: Hello, world!");
	//}

	
	// TODO: Make our own function for _registry.view<args>().each()
	for (auto [entity, transform] : _registry->view<Transform>().each()) {
		glm::vec2 pos = transform.GetPosition();

		Logger::Print("Entity has position {}, {}", pos.x, pos.y);
	}
}

void HelloSystem::Update() {
	Logger::Print("Hello, let's move the entity!");
}

void HelloSystem::End() {

}
