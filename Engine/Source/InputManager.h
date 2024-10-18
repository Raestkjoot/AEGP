#pragma once

#include <vector>

class InputManager {
public:
	void ListenToKey(unsigned int key);
	bool IsKeyDown(unsigned int key);
	bool IsKeyPressed(unsigned int key);
	bool IsKeyUp(unsigned int key);

	void KeyCallback(int key, int action, int mods);
	void Update();

private:
	struct Key {
		int keyCode;
		bool isDown;
		bool isPressed;
		bool isUp;

		Key(int keyCode) : 
			keyCode(keyCode), 
			isDown(false), isPressed(false), isUp(false) {}
	};

	std::vector<Key> _keys;
};