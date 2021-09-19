#pragma once
#include <SFMLGameEngine2.0\Window.h>
#include <SFMLGameEngine2.0\HelperFunctions.h>
#include <SFMLGameEngine2.0\VectorFunctions.h>
#include <SFMLGameEngine2.0\SpriteBatch.h>
#include <SFMLGameEngine2.0\InputManager.h>
#include <SFMLGameEngine2.0\ContactListener.h>
#include <SFML\Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void init(int width, int height);
	void input();
	void gameloop();

	GESFML::Window _window;
	GESFML::HelperFunctions _helperFunc;
	GESFML::VectorFunctions _vectorFunc;
	GESFML::SpriteBatch _spriteBatch;
	GESFML::InputManager _input;
	GESFML::InputManager _mouseinput;
	long long grabbedbody = -9999999999998;
	sf::Texture blank;
	sf::Texture Circle;
	long long id = 1000;
	b2MouseJointDef MouseJointDef;
	b2MouseJoint *MouseJoint;
	sf::Font font;

};

