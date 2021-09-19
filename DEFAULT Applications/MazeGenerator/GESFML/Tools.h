#pragma once
#include <SFML\Graphics.hpp>


namespace GESFML {

	class Tools
	{
	public:
		const void setSizeInPixel(sf::Sprite &sprite, float x, float y);
		const sf::Vector2f vectorNormalize(sf::Vector2f vec);
		const float vectorGetLength(sf::Vector2f vec);
		const float vectorDistnace(sf::Vector2f from, sf::Vector2f to);

		const sf::Texture createBlankTexture(int width, int height,sf::Color color);
		const sf::Texture createTextuerPixelData(int width, int height, sf::Uint8* pixels);

		const unsigned long xorshf96(void) {          //period 2^96-1
			static unsigned long x = 123456789, y = 362436069, z = 521288629;
			unsigned long t;
			x ^= x << 16;
			x ^= x >> 5;
			x ^= x << 1;

			t = x;
			x = y;
			y = z;
			z = t ^ x ^ y;

			return z;
		}

};

}