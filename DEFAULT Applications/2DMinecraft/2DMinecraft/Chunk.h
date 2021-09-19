#pragma once
#include "Block.h"
#include <GESFML\SpriteBatch.h>
#include <Box2D\Box2D.h>
#include <GESFML\Tools.h>
#include <GESFML\Entity.h>
#include <unordered_map>
class Chunk
{
public:
	Chunk();
	Chunk(int x, int y, int w, int h, sf::Texture &Textures,b2World *world);
	~Chunk();

	void generate(int x,int y,int w, int h, sf::Texture &Textures, b2World *world);
	void insertBlock(Block block, sf::Texture &TextureAtlas);
	void removeBlock(int x, int y);
	void destroyEnt(long long unsigned id);
	void setColor(long long unsigned id, sf::Color color);
	b2Body *getBody(long long unsigned id);
	void clearDestroyList();
	GESFML::Entity getEntity(int x, int y, int &index);
	bool isInChunk(sf::Vector2f pos);

	b2World *getWorld(){
		return _world;
	}

	sf::Vector2f getPosition() {
		return _pos;
	}

	sf::Vector2f getSize() {
		return _size;
	}

	std::unordered_map<long long unsigned, GESFML::Entity> getEntities() {
		return _entities;
	}

	std::unordered_map<long long unsigned, long long unsigned> getDestroyList() {
		return _destroyEntslist;
	}

private:
	b2World *_world;
	sf::Vector2f _pos;
	sf::Vector2f _size;
	std::unordered_map<long long unsigned, GESFML::Entity> _entities;
	std::unordered_map<long long unsigned, long long unsigned> _destroyEntslist;
	GESFML::Tools _tools;
	int id;
	int id2;
};

