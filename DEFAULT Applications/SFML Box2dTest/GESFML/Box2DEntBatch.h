#pragma once
#include "SpriteBatch.h"
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <map>

namespace GESFML {

	class Box2DEntBatch
	{
	public:
		Box2DEntBatch();
		~Box2DEntBatch();

		void initWorld(b2World*_world);
		void initWorld(b2Vec2 Gravity,float timestepfps, int iterations ,bool doSleep);

		void addRect(long long unsigned id ,int x, int y, int w, int h,bool dyn, sf::Texture &texture);
		SpriteBatch getSpriteBatch() {
			return _spriteBatch;
		}
		std::map<long long unsigned, b2Body*> getBodys() {
			return _bodys;
		}

		void update(long long unsigned id);
		void updateAll();

		void updateWorld();

		std::map<long long unsigned, b2Body*> _bodys;
		SpriteBatch _spriteBatch;
		b2World *_world;
		b2Vec2 _gravity = b2Vec2(0, 9.8f);
		float _size = 30;
		bool _doSleep = true;
		int _iterations = 10;
		float _timestep = 1.0f / 60.0f;

	};

}