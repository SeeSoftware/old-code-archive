#pragma once
#include <SFML\Graphics.hpp>
#include "Texture.h"

namespace GESFML {

	class Entity
	{
	public:
		
		Entity();
		~Entity();

		void setTexture(Texture texture);

		Texture getTexture() {
			return _texture;
		}

		void setScale(int x, int y);
		void setPosition(int x, int y);
		void setRotation(int rot);
		void setColor(sf::Color color) {
			_sprite.setColor(color);
		}
		void setPosScale(int xpos, int ypos, int xsize, int ysize);

		void move(int x, int y);
		void scale(int x, int y);
		void rotate(int rot);

		sf::Vector2f getScale() {
			return _scale;
		}

		sf::Vector2f getPosition() {
			return _pos;
		}

		float getRotation(){
			return _rot;
		}

		void setSprite(sf::Sprite sprite) {
			_sprite = sprite;
		}
		sf::Color getColor() {
			return _sprite.getColor();
		}

		sf::Sprite getSprite() {
			return  _sprite;
		}
	private:
		sf::Sprite _sprite;
		Texture _texture;
		sf::Vector2f _textureSize;

		sf::Vector2f _scale;
		sf::Vector2f _pos;
		float _rot;
	};

}