#pragma once

#include <vector>

class InputManager {
public:
	void ListenToKey(unsigned int key);
	// Returns true during the frame the user starts pressing down the key
	bool GetKeyDown(unsigned int key);
	// Returns true while the user holds down the key
	bool GetKey(unsigned int key);
	// Returns true during the frame the user releases the key
	bool GetKeyUp(unsigned int key);

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