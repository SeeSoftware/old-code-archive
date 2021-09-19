#pragma once

#include <SFML\Graphics.hpp>

namespace GESFML
{

	class HelperFunctions
	{
	public:

		const static void setSizeInPixel(sf::Sprite &sprite, float x, float y);
		const static sf::Vector2f getSizeInPixel(sf::Sprite &sprite);
		const static sf::Texture createBlankTexture(int width, int height, sf::Color color);
		const static sf::Texture createTextuerPixelData(int width, int height, sf::Uint8* pixels);
		const static unsigned long randomNumber();
		const static long long randomNumberRange(long long from, long long to);

		const static unsigned long xorshf96(void)
		{          //period 2^96-1
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
