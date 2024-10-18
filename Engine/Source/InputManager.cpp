#include "InputManager.h"

#include "Logger.h"

#include <GLFW/glfw3.h>

void InputManager::ListenToKey(unsigned int key) {
	_keys.emplace_back(key);
}

bool InputManager::IsKeyDown(unsigned int keyCode) {
	for (auto& key : _keys) {
		if (key.keyCode == keyCode) {
			return key.isDown;
		}
	}

	Logger::PrintWarning("Key not found");
	return false;
}

bool InputManager::IsKeyPressed(unsigned int keyCode) {
	for (auto& key : _keys) {
		if (key.keyCode == keyCode) {
			return key.isPressed;
		}
	}

	Logger::PrintWarning("Key not found");
	return false;
}

bool InputManager::IsKeyUp(unsigned int keyCode) {
	for (auto& key : _keys) {
		if (key.keyCode == keyCode) {
			return key.isUp;
		}
	}

	Logger::PrintWarning("Key not found");
	return false;
}

void InputManager::KeyCallback(int keyCode, int action, int mods) {
	for (auto& key : _keys) {
		if (key.keyCode != keyCode) {
			continue;
		}

		switch (action)
		{
		case GLFW_RELEASE:
			key.isPressed = false;
			key.isUp = true;
			break;
		case GLFW_PRESS:
			if (key.isPressed == false) {
				key.isDown = true;
			}
			key.isPressed = true;
			break;
		}
	}
}

void InputManager::Update() {
	for (auto& key : _keys) {
		key.isDown = false;
		key.isUp = false;
	}
}