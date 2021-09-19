#pragma once
#include <GESFML\Tools.h>
#include <SFML\Graphics.hpp>
#include <GESFML\InputManager.h>
#include <vector>

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

	void generateMaze(int width, int height,sf::Color color);
	void showSolution();

	sf::Color getPixelColor(long long ptr, int height, sf::Uint8 *pixels);
	void setPixelColor(long long ptr, int height, sf::Uint8 *pixels, sf::Color color);
	long long XYtoPtr(int x, int y, int height);
	
	GESFML::Tools _tools;	
	GESFML::InputManager _keyboard;
	
	sf::RenderWindow _window;
	sf::Sprite _canvas; 

	std::vector<sf::Vector2i> _posStack;
	std::vector<sf::Vector2i> _possiblePoints;
	std::vector<int> _possibledirection;

	bool _slowGeneration = false;
	bool _showedSolution = false;

	sf::Texture _mazeTexture;
	sf::Uint8 *pixels;

	int _width, _height;
	int _mazeWidth, _mazeHeight;
	int _pixelsize;

	sf::Color _bgColor;
	sf::Color _MazeColor = sf::Color(255,255,255,255);

	int _generationspeed = 60;
	bool _generating = false;

};

