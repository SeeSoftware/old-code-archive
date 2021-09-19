#pragma once
#include <GESFML\Entity.h>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
class Player
{
public:
	Player();
	Player(sf::Vector2f position,sf::Texture &playerTexture,b2World *_world);
	~Player();

	void move(sf::Vector2f velocity);

	GESFML::Entity getEntity() {
		return _entity;
	}

	sf::Sprite getSprite() {
		return _entity.getSprite();
	}

	void init(sf::Vector2f position, sf::Texture  &playerTexture, b2World *_world);

	void update();

	sf::Vector2f getPosition() {
		return _entity.getSprite().getPosition();
	}

private:
	GESFML::Entity _entity;
};

