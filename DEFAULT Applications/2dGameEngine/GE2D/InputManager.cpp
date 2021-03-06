#include "InputManager.h"

namespace GE2D {

	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::pressKey(unsigned int keyID) {
		_keyMap[keyID] = true;

	}

	void InputManager::releaseKey(unsigned int keyID) {
		_keyMap[keyID] = false;

	}

	void InputManager::setMouseCoords(float x, float y) {
		_mouseCoords.x = x;
		_mouseCoords.y = y;

	}

	bool InputManager::isKeyPressed(unsigned int keyID) {
		auto it = _keyMap.find(keyID);
		if (it != _keyMap.end()) {
			return it->second;
		}
		else
		{
			return false;
		}

	}


}