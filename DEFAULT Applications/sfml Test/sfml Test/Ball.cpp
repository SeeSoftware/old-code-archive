#include "Ball.h"
#include <iostream>

Ball::Ball(sf::Texture &texture)
{
	
	_randomseed++;
	float random;
	float random2;
	srand(_randomseed);
	random = rand() % 100;
	_randomseed++;
	srand(_randomseed);
	std::cout << _randomseed;
	random2 = rand() % 100;

	_texture = texture;

	_sprite.setTexture(texture);
	_sprite.setScale(sf::Vector2f(0.1f+(random/500), 0.1f+(random/500) ));
	_sprite.setPosition(sf::Vector2f(random*2 + 100, random*2 + 100));
	_sprite.setColor(sf::Color(255, 255, 255));

	_veclocity = sf::Vector2f(random / 2060- (random / 2060)/2 + 0.01f, random2 / 2060 + 0.01f);
}


Ball::~Ball()
{
}

void Ball::update() {
	_sprite.move(_veclocity);
	if (_sprite.getPosition().y > 600) {
		_veclocity.y = _veclocity.y *-1;
	}
	if (_sprite.getPosition().y < 0) {
		_veclocity.y = _veclocity.y *-1;
	}

	if (_sprite.getPosition().x > 800) {
		_veclocity.x = _veclocity.x *-1;
	}

	if (_sprite.getPosition().x < 0) {
		_veclocity.x = _veclocity.x *-1;
	}
}

void Ball::draw(sf::RenderWindow &window) {
	window.draw(_sprite);

}