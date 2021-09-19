#include "World.h"
#include <random>


World::World(int x, int y, int xs, int ys, std::unordered_map < std::string, sf::Texture> &textures)
{
	init(x, y, xs, ys, textures);
}

World::World()
{
	
}

World::~World()
{
	
}

void World::init(int x, int y, int xs, int ys, std::unordered_map < std::string, sf::Texture> &textures) {
	int id = 0;
	int randomNum = 0;
	std::random_device rd;   // non-deterministic generator
	std::mt19937 gen(rd());  // to seed mersenne twister.
	std::uniform_int_distribution<> dist(1, 30); // distribute results between 1 and 30 inclusive.
	std::uniform_int_distribution<> distStone(1, 2); // distribute results between 1 and 2 inclusive.
	std::uniform_int_distribution<> distColor(225, 255); // distribute results between 1 and 255 inclusive.

	for (int j = y; j < ys; j++) {
		for (int k = x; k < xs; k++)
		{
			randomNum = dist(gen);

			if (randomNum == 1) 
			{
				int color = distColor(gen);

				int randomStone = distStone(gen);
				if (randomStone == 1)
				{
					_worldSpriteBatch.createSprite(id, j*BLOCKSIZE, k*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, textures["Stone1"]);
					_worldSpriteBatch.setColor(id, sf::Color(color, color, color));
				}
				else
				{
					_worldSpriteBatch.createSprite(id, j*BLOCKSIZE, k*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, textures["Stone2"]);
					_worldSpriteBatch.setColor(id, sf::Color(color, color, color));
				}
			}
			else
			{
				int color = distColor(gen);

				_worldSpriteBatch.createSprite(id, j*BLOCKSIZE, k*BLOCKSIZE, BLOCKSIZE, BLOCKSIZE, textures["Grass"]);
				_worldSpriteBatch.setColor(id, sf::Color(color, color, color));
			}
			id++;
		}
	}
}

GESFML::SpriteBatch World::getSpriteBatch() {
	return _worldSpriteBatch;
}
