#include "System.h"

void System::Start() {}

void System::Update(float delta) {}

void System::End() {}

void System::Init(entt::registry* registry) {
	_registry = registry;
}