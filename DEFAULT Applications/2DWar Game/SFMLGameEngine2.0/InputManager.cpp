#include "InputManager.h"

namespace GESFML
{
	InputManager::InputManager()
	{
	}


	InputManager::~InputManager()
	{
	}

	void InputManager::releaseKey(int key)
	{

			_keyMap[key] = false;
			if (_keyMap.count(key) > 0)
			{
			releasedKey = key;
			}
	}

	void InputManager::pressKey(int key)
	{

			_keyMap[key] = true;
		if (_keyMap.count(key) > 0)
		{
			pressedKey = key;
		}
	}

	bool InputManager::getKey(int key)
	{
		return _keyMap[key];

	}

	bool InputManager::getAndClearKey(int key)
	{
		bool tmp;
		tmp = _keyMap[key];
		releaseKey(key);
		return tmp;
	}

	int InputManager::getKeyPressed()
	{
		int tmp;
		tmp = pressedKey;
		releasedKey = -1;
		pressedKey = -1;
		return tmp;
	}

	int InputManager::getKeyReleased()
	{
		int tmp;
		tmp = releasedKey;
		pressedKey = -1;
		releasedKey = -1;
		return tmp;
	}

	void InputManager::clearKeys()
	{
		_keyMap.clear();
		releasedKey = -1;
		pressedKey = -1;

	}
}