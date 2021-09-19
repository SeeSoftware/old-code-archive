#pragma once
#include <SFML\Graphics.hpp>
#include <string>

namespace GESFML {

	class Texture
	{
	public:
		Texture(sf::Texture texture);
		Texture();
		~Texture();

		void setTexture(sf::Texture texture);

		sf::Texture getTexture() {
			return _texture;
		}



		//sf::Uint8*getPixels() {
		//	return _pixels;
		//}

		void openPng(std::string path);
		void createEmptyTexture(int width, int height);

		//void createEmptyTexture(int width, int height, sf::Color color);
		//void createTexturePixelData(int width, int height, sf::Uint8 *pixels);
		//void updateWithPixelData(sf::Uint8 *pixels);
		//void update();

	private:
		//void createEmptyTextureold(int width, int height, sf::Color color);
		sf::Texture _texture;
		//sf::Uint8 *_pixels;
		int _width;
		int _height;
	};
}

