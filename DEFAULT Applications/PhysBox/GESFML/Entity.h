#pragma once
#include <SFML\Graphics.hpp>
#include <Box2D\Box2D.h>

namespace GESFML {

	class Entity
	{
	public:
		Entity();
		~Entity();

		Entity(sf::Sprite sprite, b2Body *physObj, b2World *World);
		Entity(int x, int y, int w, int h, sf::Texture &texture, bool dyn, b2World *World);


		b2Body* getBody() {
			return _body;
		}
		sf::Sprite getSprite() {
			return _sprite;
		}
		b2World * getWorld() {
			return _world;
		}
		void setTextureRect(sf::IntRect rect);

		void initBox(int x, int y, float w, float h, sf::Texture &texture, bool dyn, b2World *World);
		void initSphere(int x, int y, float w, float h, sf::Texture &texture, bool dyn, b2World *World);
		void initBodyBox(int x, int y, float w, float h, bool dyn, b2World *world);
		void initSprite(int x, int y, float w, float h, sf::Texture &texture);
		void update();
		void updateOffset(sf::Vector2f offset);

	private:

		sf::Sprite _sprite;
		b2Body *_body;
		b2World *_world;
		sf::Vector2f _pxsize;
		bool _dyn;
	};

}