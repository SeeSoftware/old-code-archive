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
		_entities[id] = Entity(x, y, w, h, texture, dyn, _world);

	}

	void Box2DEntBatch::update(long long unsigned id) {

		_entities[id].update();
	}

	void Box2DEntBatch::updateAll() {

		for (auto &x : _entities ) {
			update(x.first);
		}
	}

	void Box2DEntBatch::updateWorld() {
		_world->Step(_timestep, _iterations, _iterations);
	}


	void Box2DEntBatch::insertEntity(long long unsigned id,Entity entity) {
		_entities[id] = entity;
	}
 

}