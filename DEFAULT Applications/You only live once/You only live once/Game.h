#pragma once
#include <SFMLGameEngine2.0\Window.h>
#include <SFML\Graphics.hpp>
#include <SFMLGameEngine2.0\HelperFunctions.h>
#include <Box2D\Box2D.h>
#include <SFMLGameEngine2.0\InputManager.h>
#include <iostream>
#include <SFMLGameEngine2.0\SpriteBatch.h>
#include <SFMLGameEngine2.0/VectorFunctions.h>
#include <unordered_map>
#include <map>
#include <string>
class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void init(int width, int height);
	void gameloop();
	void input();
	void processEntities();

	GESFML::SpriteBatch _spriteBatch;
	GESFML::HelperFunctions _helperFunc;
	GESFML::InputManager _mouseInput;
	GESFML::InputManager _keyboardInput;
	GESFML::VectorFunctions _vectorFunc;
	GESFML::Window _window;
	
	int releasedMouseKey = -2;
	int pressedMouseKey = -1;
	int releasedKey = -2;
	int pressedKey = -1;
	bool _inAir = false;

	int _width;
	int _height;

	b2MouseJoint *_dragJoint;
	b2MouseJointDef _dragJointDef;
	sf::Vector2f _cursorPos;
	std::unordered_map<std::string, sf::Texture> _textureBatch;

};

