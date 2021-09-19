#include "Tools.h"

namespace GESFML {

	const void Tools::setSizeInPixel(sf::Sprite  &sprite, float x, float y)
	{
		const sf::Texture *tmp;
		tmp = sprite.getTexture();

		sprite.setScale(x / tmp->getSize().x, y / tmp->getSize().y);

	}

	const sf::Vector2f Tools::vectorNormalize(sf::Vector2f vec) {
		sf::Vector2f vector;
		float length = vectorGetLength(vec);

		if (length != 0) {
			vector.x = vec.x / length;
			vector.y = vec.y / length;
		}

		return vector;


	}
	const float Tools::vectorGetLength(sf::Vector2f vec) {
		return sqrt(vec.x*vec.x + vec.y * vec.y);

	}
	const float Tools::vectorDistnace(sf::Vector2f from, sf::Vector2f to) {
		float distance = sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2));
		return distance;


	}

	const sf::Texture Tools::createBlankTexture(int width, int height, sf::Color color) {
		sf::Uint8 *tmp = new sf::Uint8[width*height*4];

		sf::Texture tmp_texture;

		for (int i = 0; i < width*height*4;i+=4) {

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

	const sf::Texture Tools::createTextuerPixelData(int width, int height, sf::Uint8* pixels) {

		sf::Texture tmp_texture;

		tmp_texture.create(width, height);
		tmp_texture.update(pixels);

		return tmp_texture;
	}

}