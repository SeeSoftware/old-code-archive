#include "Entity.h"
#include <iostream>

namespace GESFML {

	Entity::Entity()
	{
	}


	Entity::~Entity()
	{
	}


	Entity::Entity(sf::Sprite sprite, b2Body *physObj, b2World *World) {
		_body = physObj;
		_sprite = sprite;
		_world = World;
	}
	Entity::Entity(int x, int y, int w, int h, sf::Texture &texture, bool dyn, b2World *World) {
		init(x, y, w, h, texture, dyn, World);

	}

	void Entity::init(int x, int y, float w, float h, sf::Texture &texture, bool dyn, b2World *World) {
		_sprite.setTexture(texture);
		_sprite.setPosition(x, y);
		_sprite.setScale(w / texture.getSize().x, h / texture.getSize().y);
		_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);

		_dyn = dyn;
		_world = World;


		b2BodyDef bodyDef;
		bodyDef.position.Set(_sprite.getPosition().x, _sprite.getPosition().y);
		if (_dyn)
			bodyDef.type = b2_dynamicBody;
		b2Body * body = _world->CreateBody(&bodyDef);


		b2PolygonShape shape;
		shape.SetAsBox(w / 2, h / 2);

		b2FixtureDef fixedDef;
		fixedDef.shape = &shape;
		fixedDef.density = 1.0;
		body->CreateFixture(&fixedDef);

		_body = body;

		update();
	}

	void Entity::update() {
		if (_body == nullptr) { return; }

		_sprite.setPosition(_body->GetPosition().x, _body->GetPosition().y);
		_sprite.setRotation(_body->GetAngle()*180.0 / 3.14159265);

	}

	void Entity::setTextureRect(sf::IntRect rect) {
		_sprite.setTextureRect(rect);
	}

	void Entity::initBody(int x, int y, float w, float h, bool dyn, b2World *world) {
		_dyn = dyn;
		_world = world;


		b2BodyDef bodyDef;
		bodyDef.position.Set(x,y);
		if (_dyn)
			bodyDef.type = b2_dynamicBody;
		b2Body * body = _world->CreateBody(&bodyDef);


		b2PolygonShape shape;
		shape.SetAsBox(w / 2, h / 2);

		b2FixtureDef fixedDef;
		fixedDef.shape = &shape;
		fixedDef.density = 1.0;
		body->CreateFixture(&fixedDef);

		_body = body;

		update();
		
	}

	void Entity::setUserData(long long data) {
		_userdata = data;
	}
	long long Entity::getUserData() {
		return _userdata;
	}

	void Entity::setColor(sf::Color color) {
		_sprite.setColor(color);
	}

	void Entity::initSprite(int x, int y, float w, float h, sf::Texture &texture) {
		_sprite.setTexture(texture);
		_sprite.setPosition(x, y);
		_sprite.setScale(w / texture.getSize().x, h / texture.getSize().y);
		_sprite.setOrigin(texture.getSize().x / 2, texture.getSize().y / 2);
	}


	void Entity::updateOffset(sf::Vector2f offset) {
		if (_body == nullptr) { return; }

		_sprite.setPosition(_body->GetPosition().x+offset.x, _body->GetPosition().y+offset.y);
		_sprite.setRotation(_body->GetAngle()*180.0 / 3.14159265);

	}


}