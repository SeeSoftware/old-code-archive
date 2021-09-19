#pragma once
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
	void gameLoop();

	int _width;
	int _height;

	sf::RenderWindow _window;

};

