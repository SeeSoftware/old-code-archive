#include "Block.h"



Block::Block(int x, int y, int blockid, sf::Texture &_texture, b2World *_world)
{
	blockid = blockid;
	blockPosX = x;
	blockPosY = y;

	_entity = GESFML::Entity();
	_entity.initSprite(x*_blockSize + (_texture.getSize().x*_blockSize / 16 / 2), y*_blockSize + (_texture.getSize().y*_blockSize / 16 / 2), _texture.getSize().x*_blockSize / 16, _texture.getSize().y*_blockSize / 16, _texture);
	//_entity = GESFML::Entity(x*_blockSize, y*_blockSize, _blockSize, _blockSize, _texture, false, _world);
	_entity.initBody(x*_blockSize, y*_blockSize, _blockSize, _blockSize, false, _world);
	_entity.updateOffset(sf::Vector2f((_texture.getSize().x*_blockSize / 16) / 2 - 25, (_texture.getSize().y*_blockSize / 16) / 2 - 25));
	_entity.setTextureRect(sf::IntRect(blockid % 16 * 16, blockid / 16 * 16, 16, 16));
	_entity.setUserData(blockid);
	_entity.getBody()->GetFixtureList()->SetFriction(0);
}

Block::Block()
{

}

Block::~Block()
{
}

void Block::create(int x, int y, int blockid, sf::Texture &_texture, b2World *_world) {
	blockid = blockid;
	blockPosX = x;
	blockPosY = y;

	_entity = GESFML::Entity();
	_entity.initSprite(x*_blockSize + (_texture.getSize().x*_blockSize / 16 / 2), y*_blockSize + (_texture.getSize().y*_blockSize / 16 / 2), _texture.getSize().x*_blockSize / 16, _texture.getSize().y*_blockSize / 16, _texture);
	//_entity = GESFML::Entity(x*_blockSize, y*_blockSize, _blockSize, _blockSize, _texture, false, _world);
	_entity.initBody(x*_blockSize, y*_blockSize, _blockSize, _blockSize, false, _world);
	_entity.updateOffset(sf::Vector2f((_texture.getSize().x*_blockSize / 16) / 2-12.5f, (_texture.getSize().y*_blockSize / 16) / 2- 12.5f));
	_entity.setTextureRect(sf::IntRect(blockid % 16 * 16, blockid / 16 * 16, 16, 16));
	_entity.setUserData(blockid);
	_entity.getBody()->GetFixtureList()->SetFriction(0);
	
}