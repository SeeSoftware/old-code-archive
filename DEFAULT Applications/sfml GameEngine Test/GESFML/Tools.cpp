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

}