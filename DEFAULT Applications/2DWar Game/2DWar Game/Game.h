#pragma once
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <Box2D\Box2D.h>
#include <SFMLGameEngine2.0\HelperFunctions.h>
#include <SFMLGameEngine2.0\InputManager.h>
#include <SFMLGameEngine2.0\SpriteBatch.h>
#include <SFMLGameEngine2.0\VectorFunctions.h>
#include <SFMLGameEngine2.0\Window.h>
#include <SFMLGameEngine2.0\Vector2D.h>
#include <SFMLGameEngine2.0\Color.h>
#include <unordered_map>
#include <thread>

#define BLOCK_PIXELSIZE 32
#define AMMOUNT_OF_CHUNKS_TO_GENERATE 32


class Game
{
public:
	Game();
	~Game();
	void run();

private:

	void init(int w, int h);
	void input();
	void gameLoop();
	void processEntities();
	long long findNextFreeId();
	long long findNextFreeIdSprite();
	void createBlock(int x, int y, int blockId);
	void deleteBlock(int x, int y);

	sf::Font _DefaultFont;

	GESFML::Window _window;
	GESFML::SpriteBatch _spriteBatch;
	GESFML::VectorFunctions _vectorFuncs;
	GESFML::HelperFunctions _helperFuncs;
	GESFML::InputManager _keyboardInput;
	GESFML::InputManager _mouseInput;

	std::unordered_map<std::string, sf::Texture> _textureBatch;
	std::unordered_map<std::string, long long> _guiElements;
	std::unordered_map<long long, std::unordered_map<long long, long long> > _worldBlocks;
	std::unordered_map<std::string, long long> _worldEntities;
	std::unordered_map<long long, std::unordered_map<std::string, std::string> > _entityDataStr;
	std::unordered_map<long long, std::unordered_map<std::string, long double> > _entityDataNum;

	sf::Time _frametime;

	bool _canSpawn = true;
	bool _canUpdate = true;
	bool _canDraw = true;
	bool _isDrawing = false;
	bool _runGenerateFunction = false;
	GESFML::Vector2D _mousePos = GESFML::Vector2D(0,0);

	int _ammountOfChunksGenerated = 0;
	long long _ammountOfBlocksPlaced = 0;

	int _width;
	int _height;
	int _mousePressed = -1;
	int _mouseReleased = -1;
	int _keyPressed = -1;
	int _keyReleased = -1;
	//int tmp = -1;
};

