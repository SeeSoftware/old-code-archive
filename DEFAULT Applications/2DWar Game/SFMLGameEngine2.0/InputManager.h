#pragma once
#include<unordered_map>
#include<SFML\Graphics.hpp>

namespace GESFML
{

	class InputManager
	{
	public:
		InputManager();
		~InputManager();

		void releaseKey(int key);
		void pressKey(int key);

		bool getKey(int key);
		bool getAndClearKey(int key);
		int getKeyPressed();
		int getKeyReleased();
		void clearKeys();

		std::unordered_map<int, bool> getKeyMap()
		{
			return _keyMap;
		}

	private:
		std::unordered_map<int, bool> _keyMap;

		int releasedKey=-1;
		int pressedKey=-1;
	};

}

