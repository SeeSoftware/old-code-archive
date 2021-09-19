#pragma once
#include <SFML\Graphics.hpp> 
#include <GESFML\Box2DEntBatch.h>
#include <GESFML\InputManager.h>
#include <GESFML\SpriteBatch.h>
#include <GESFML\Tools.h>
#include <vector>
#include "Block.h"
#include "Chunk.h"
#include "Player.h"
#include <map>
#include <SFML\Audio.hpp>
#include <unordered_map>


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
	int getChunk(sf::Vector2f pos);
	
	//void generateChunk(int x, int y, int w, int h);

	//void occlusion();

	GESFML::Tools _tools;
	GESFML::Box2DEntBatch _physEnt;
	GESFML::SpriteBatch _gui;
	GESFML::InputManager _ioManager;
	GESFML::InputManager _ioMouse;
	sf::RenderWindow _window;
	sf::Texture _textureAtlas;
	sf::Texture _playerTexture;
	sf::View _camera;
	sf::Color _bgColor;
	sf::Sound _music;
	sf::SoundBuffer _buffer;

	Player _player;
	
	std::map<long long unsigned, Chunk> _chunkBatch;

	GESFML::SpriteBatch _renderBatch;

	int _width;
	int _height;
	int _id = 0;
	int _tmp;
	int _selectedBlock=1;

	std::unordered_map<long long unsigned, std::string> _blocks_names;
	std::unordered_map<long long unsigned, long long> _blocks_id;

	sf::Text _selectionText;
	sf::Font _font;
	sf::Vector2f _lastmousepos;

};

