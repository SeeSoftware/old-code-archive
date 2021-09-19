#pragma once
#include <SFML\Graphics.hpp>
#include <GESFML\InputManager.h>
#include <GESFML\Box2DEntBatch.h>
#include <GESFML\SpriteBatch.h>
#include <GESFML\Tools.h>
#include <Box2D\Box2D.h>
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

	int _width, _height,_tmp=0,_id=4;
	
	sf::RenderWindow _window;
	GESFML::SpriteBatch _gui;
	GESFML::SpriteBatch _background;
	GESFML::InputManager _keyboard;
	GESFML::InputManager _mouse;
	GESFML::Box2DEntBatch _ents;
	GESFML::Tools _tools;
	sf::View _camera;
	std::map<std::string, sf::Texture> _textures;

};

