#pragma once
#include <SFML\Graphics.hpp>
#include <time.h>
class Ball
{
public:
	Ball(sf::Texture &texture);
	~Ball();

	void update();
	void draw(sf::RenderWindow &window);
private:
	sf::Sprite _sprite;
	sf::Texture _texture;
	sf::Vector2f _veclocity;
	int _randomseed = time(NULL);
};

