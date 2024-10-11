#include "Scene.h"

void Scene::Start() {
	for (auto& system : _systems) {
		system->Start();
	}
}

void Scene::Update() {}

void Scene::End() {}

entt::entity Scene::CreateEntity() {
	return _registry.create();
}

void Scene::AddComponent() {}

void Scene::AddSystem(std::unique_ptr<System> system) {
	system->Init(&_registry);
	_systems.push_back(std::move(system));
}