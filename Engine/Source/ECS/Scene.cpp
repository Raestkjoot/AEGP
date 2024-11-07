#include "Scene.h"

void Scene::Initialize() {
	for (auto& system : _systems) {
		system->Init(&_registry);
	}
}

void Scene::Start() {
	for (auto& system : _systems) {
		system->Start();
	}
}

void Scene::Update(float delta) {
	for (auto& system : _systems) {
		system->Update(delta);
	}
}

void Scene::End() {
	for (auto& system : _systems) {
		system->End();
	}
}

entt::entity Scene::CreateEntity() {
	return _registry.create();
}

void Scene::AddSystem(std::unique_ptr<System> system) {
	if (system.get() == nullptr) {
		return;
	}

	_systems.push_back(std::move(system));
}