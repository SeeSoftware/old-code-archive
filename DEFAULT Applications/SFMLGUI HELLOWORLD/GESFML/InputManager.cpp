#include "InputManager.h"


namespace GESFML {
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::releaseKey(int key) {
		_keyMap[key] = false;
	}

	void InputManager::pressKey(int key) {
		_keyMap[key] = true;
	}

	bool InputManager::getKey(int key) {
		return _keyMap[key];

	}

	void InputManager::clearKeys() {
		_keyMap.clear();

	}
}