#pragma once
#include <SFML\Graphics.hpp>
#include <GESFML\SpriteBatch.h>
#include <GESFML\InputManager.h>
#include <GESFML\Box2DEntBatch.h>
#include <GESFML\Tools.h>
#include <Box2D\Box2D.h>

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


	GESFML::InputManager _ioManager;
	GESFML::Tools _tools;
	GESFML::SpriteBatch _batch;
	GESFML::Box2DEntBatch _Box2DBatch;

	sf::RenderWindow _window;
	
	int _id=0;
	sf::Texture _texture;

};

