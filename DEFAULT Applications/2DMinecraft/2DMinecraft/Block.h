#pragma once
#include <GESFML\Entity.h>
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>
#include <string>
class Block
{
public:
	Block(int x, int y,int blockid, sf::Texture &_texture,b2World *_world);
	Block();
	~Block();

	void create(int x, int y, int blockid, sf::Texture &_texture, b2World *_world);

	int blockid;
	int blockPosX;
	int blockPosY;

	GESFML::Entity getEntity() {
		return _entity;
	}
	sf::Sprite getSprite() {
		return _entity.getSprite();
	}

private:
	const int _blockSize = 25;
	GESFML::Entity _entity;
	sf::Texture _texture;
};

