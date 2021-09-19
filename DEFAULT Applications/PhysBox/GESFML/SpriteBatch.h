#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "Tools.h"
#include <map>

namespace GESFML {

	class SpriteBatch
	{
	public:
		SpriteBatch();
		~SpriteBatch();

		void createSprite(long long unsigned id);
		void createSprite(long long unsigned id, int x, int y, int xs, int ys);
		void createSprite(long long unsigned id, int x, int y, int xs, int ys, sf::Texture &texture);

		sf::Vector2f getPosition(long long unsigned id);
		sf::Vector2f getScale(long long unsigned id);
		sf::Vector2f getScaleInPixel(long long unsigned id);
		float getRotation(long long unsigned id);
		const sf::Texture *getTexture(long long unsigned id);
		sf::Color getColor(long long unsigned id);

		void setPosition(long long unsigned id, int x, int y);
		void setTexture(long long unsigned id, sf::Texture &texture);
		void setScale(long long unsigned id, int x, int y);
		void setScaleInPixel(long long unsigned id, int x, int y);
		void setRotation(long long unsigned id, float rotation);
		void setColor(long long unsigned id,sf::Color color);

		void move(long long unsigned id, int x, int y);
		void scale(long long unsigned id, int x, int y);
		void scaleInPixel(long long unsigned id, int x, int y);
		void rotatate(long long unsigned id, int rot);

		void setSprite(long long unsigned id, sf::Sprite sprite);
		sf::Sprite getSprite(long long unsigned id);

		long long unsigned getSize();
		void deleteAll();
		void deleteSprite(long long unsigned id);



		std::map<long long unsigned, sf::Sprite> getSprites() {
			return _sprites;
		}
		
		std::map<long long unsigned, sf::Sprite>::key_compare getSpritesKeyCompare() {
			return _sprites.key_comp();
		}

	private:
		std::map<long long unsigned, sf::Sprite> _sprites;
		Tools _tools;

		
	};

}