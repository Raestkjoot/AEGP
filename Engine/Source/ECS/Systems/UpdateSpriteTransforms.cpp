#include "UpdateSpriteTransforms.h"

#include "ECS/Components/Transform.h"
#include "Logger.h"

void UpdateSpriteTransforms::Start() {

}

void UpdateSpriteTransforms::Update() {
	auto view = _registry->view<Transform>();
	
	_testValue++;
	if (_testValue % 2 == 0) {
		for (auto [entity, transform] : view.each()) {
			// TODO: Update transforms in the sprite draw call.
			if (transform._dirty) {
				glm::vec2 pos = transform.GetPosition();
				transform._dirty = false;
				Logger::Print("Entity has moved to position {}, {}", pos.x, pos.y);
			}
		}
	} else { // TODO: This is a test case, remove it when done with testing
		for (auto [entity, transform] : view.each()) {
			transform.SetPosition({ _testValue, _testValue });
		}
	}


}

void UpdateSpriteTransforms::End() {

}

void UpdateSpriteTransforms::Init(entt::registry* registry) {
	System::Init(registry);
}
