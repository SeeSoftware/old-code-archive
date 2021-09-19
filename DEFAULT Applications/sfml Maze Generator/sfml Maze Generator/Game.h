#pragma once
#include <SFML\Graphics.hpp>
#include <GESFML\Window.h>
#include <vector>

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

	void runstep();

	int _width;
	int _height;

	GESFML::Window _window;
	sf::Uint8* _pixels;

	void setPixel(int x, int y, sf::Color color);
	sf::Color getPixel(int x, int y);

	std::vector<sf::Vector2f> _positions;
	sf::Vector2f _currentPos;
	int _randomseed;
};
