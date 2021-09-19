#pragma once
#include <GESFML\SpriteBatch.h>
#include <SFML\Graphics.hpp>
#include <unordered_map>

class World
{
public:
	World(int x, int y, int xs, int ys, std::unordered_map < std::string, sf::Texture> &textures);
	World();
	~World();

	void init(int x, int y, int xs, int ys, std::unordered_map < std::string, sf::Texture> &textures);
	GESFML::SpriteBatch getSpriteBatch();

private:
	const int BLOCKSIZE = 32;
	GESFML::SpriteBatch _worldSpriteBatch;
	
};

