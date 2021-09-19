#include "HelperFunctions.h"
#include <random>

namespace GESFML
{

	const void HelperFunctions::setSizeInPixel(sf::Sprite &sprite, float x, float y)
	{
		const sf::Texture *tmp;
		tmp = sprite.getTexture();

		sprite.setScale(x / tmp->getSize().x, y / tmp->getSize().y);
	}

	const sf::Texture HelperFunctions::createBlankTexture(int width, int height, sf::Color color)
	{
		sf::Uint8 *tmp = new sf::Uint8[width*height * 4];

		sf::Texture tmp_texture;

		for (int i = 0; i < width*height * 4;i += 4)
		{

			tmp[i] = color.r;
			tmp[i + 1] = color.g;
			tmp[i + 2] = color.b;
			tmp[i + 3] = color.a;

		}

		tmp_texture.create(width, height);
		tmp_texture.update(tmp);

		delete[] tmp;

		return tmp_texture;
	}

	const sf::Texture HelperFunctions::createTextuerPixelData(int width, int height, sf::Uint8* pixels)
	{
		sf::Texture tmp_texture;

		tmp_texture.create(width, height);
		tmp_texture.update(pixels);

		return tmp_texture;
	}

	const unsigned long HelperFunctions::randomNumber()
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		return gen();
	}

	const long long HelperFunctions::randomNumberRange(long long from, long long to)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(from, to);

		return dist(gen);
	}

	const sf::Vector2f HelperFunctions::getSizeInPixel(sf::Sprite &sprite)
	{
		const sf::Texture *tmp;
		sf::Vector2f tmpvec;
		tmp = sprite.getTexture();
		tmpvec = sf::Vector2f(tmp->getSize());

		return sf::Vector2f(sprite.getScale().x*tmpvec.x,sprite.getScale().y*tmpvec.y);
	}

}