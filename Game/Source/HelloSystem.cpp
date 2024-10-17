#include "HelloSystem.h"

#include "Logger.h"
#include "ECS/Components/Transform.h"

void HelloSystem::Start() {
	// This is the way to get all entities
	// TODO: Might want to make our own function for this too?
	//for (auto entity : _registry->view<entt::entity>()) {

	// TODO: Make our own function for _registry.view<args>().each()
	//for (auto [entity, transform] : _registry->view<Transform>().each()) {

	Logger::Print("Hello, Start()!");
}

void HelloSystem::Update() {
	Logger::Print("Hello, Update()!");
}

void HelloSystem::End() {
	Logger::Print("Hello, End()!");
}
