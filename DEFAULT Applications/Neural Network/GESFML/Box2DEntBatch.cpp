#include "Box2DEntBatch.h"

namespace GESFML {

	Box2DEntBatch::Box2DEntBatch()
	{
	}


	Box2DEntBatch::~Box2DEntBatch()
	{
	}

	void Box2DEntBatch::initWorld(b2World*_world) {

	}
	void Box2DEntBatch::initWorld(b2Vec2 Gravity, float timestepfps, int iterations, bool doSleep) {

		_world = new b2World(Gravity);
		_world->SetAllowSleeping(doSleep);

		_iterations = iterations;
		_doSleep = doSleep;
		_timestep = 1.0f / timestepfps;
		_gravity = Gravity;

	}

	void Box2DEntBatch::addRect(long long unsigned id, int x, int y, int w, int h, bool dyn, sf::Texture &texture) {
		b2BodyDef bodyDef;
		bodyDef.position.Set(x, y);
		if (dyn)
			bodyDef.type = b2_dynamicBody;
		b2Body * body = _world->CreateBody(&bodyDef);


		b2PolygonShape shape;
		shape.SetAsBox(w / 2, h / 2);

		b2FixtureDef fixedDef;
		fixedDef.shape = &shape;
		fixedDef.density = 1.0;
		body->CreateFixture(&fixedDef);

		_bodys[id] = body;
		_spriteBatch.createSprite(id, x, y, w, h, texture);

	}

	void Box2DEntBatch::update(long long unsigned id) {

		if (_bodys[id] == nullptr) { return; }


			_spriteBatch.setPosition(id, _bodys[id]->GetPosition().x, _bodys[id]->GetPosition().y);
			sf::Sprite tmp = _spriteBatch.getSprite(id);
			tmp.setOrigin(sf::Vector2f(_spriteBatch.getTexture(id)->getSize().x / 2, _spriteBatch.getTexture(id)->getSize().y / 2));
			tmp.setRotation(_bodys[id]->GetAngle()*180.0 / 3.14159265);
			_spriteBatch.setSprite(id, tmp);
		
	}

	void Box2DEntBatch::updateAll() {

		for (auto &x : _bodys ) {
			update(x.first);
		}
	}

	void Box2DEntBatch::updateWorld() {
		_world->Step(_timestep, _iterations, _iterations);
	}


	void Box2DEntBatch::insertBody(long long unsigned id, b2Body *body,sf::Texture &texture) {
		_bodys[id] = body;
		_spriteBatch.createSprite(id, 0, 0, 0, 0, texture);
		update(id);
	}
 

}