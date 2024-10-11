#include "HelloSystem.h"

#include "Logger.h"

void HelloSystem::Start() {
	for (auto entity : _registry->view<entt::entity>()) {
		Logger::Print("Entt: Hello, world!");
	}
}

void HelloSystem::Update() {

}

void HelloSystem::End() {

}
