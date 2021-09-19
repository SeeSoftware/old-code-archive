#pragma once
#include <SFML\Graphics.hpp>
#include <GESFML\Tools.h>
#include <GESFML\InputManager.h>
#include <GESFML\SpriteBatch.h>
#include <unordered_map>
#include <string>
#include "World.h"
class Game
{
public:
	Game();
	~Game();

	void run();

private:

	void init(int MainWidth, int MainHeight,int SecondWidth, int SecondHeight);
	void input_main();
	void input_second();
	void mainloop();
	
	int _mainWidht,_mainHeight,_secondWidth,_secondHeight;
	
	sf::RenderWindow _mainWindow;
	sf::RenderWindow _secondWindow;
	sf::View _mainCamera;

	GESFML::InputManager _mainWindowInput;
	GESFML::InputManager _secondWindowInput;
	
	GESFML::Tools _tools;
	std::unordered_map<std::string, sf::Texture> _textures;
	World _world;
};

