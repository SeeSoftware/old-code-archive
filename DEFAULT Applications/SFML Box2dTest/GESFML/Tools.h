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
};

}