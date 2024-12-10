#include "InputManager.h"

#include "Utils/Logger.h"

#include <GLFW/glfw3.h>

void InputManager::ListenToKey(unsigned int keyCode) {
	for (auto key : _keys) {
		if (key.keyCode == keyCode) {
			Logger::PrintWarning("InputManager: Key {} is already listened to!", keyCode);
			return;
		}
	}

	_keys.emplace_back(keyCode);
}

bool InputManager::GetKeyDown(unsigned int keyCode) {
	for (auto& key : _keys) {
		if (key.keyCode == keyCode) {
			return key.isDown;
		}
	}

	Logger::PrintWarning("Key {} not found. Adding to listen list.", keyCode);
	ListenToKey(keyCode);
	return false;
}

bool InputManager::GetKey(unsigned int keyCode) {
	for (auto& key : _keys) {
		if (key.keyCode == keyCode) {
			return key.isPressed;
		}
	}

	Logger::PrintWarning("Key {} not found. Adding to listen list.", keyCode);
	ListenToKey(keyCode);
	return false;
}

bool InputManager::GetKeyUp(unsigned int keyCode) {
	for (auto& key : _keys) {
		if (key.keyCode == keyCode) {
			return key.isUp;
		}
	}

	Logger::PrintWarning("Key {} not found. Adding to listen list.", keyCode);
	ListenToKey(keyCode);
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