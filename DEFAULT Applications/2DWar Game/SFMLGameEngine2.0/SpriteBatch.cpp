#include "SpriteBatch.h"
#include <iostream>
#include "ContactListener.h"
#include "Indexer.h"
namespace GESFML
{

	SpriteBatch::SpriteBatch()
	{
	}


	SpriteBatch::~SpriteBatch()
	{
		delete _world;
		delete _contactInstance;
	}

	void SpriteBatch::initWorld(b2Vec2 gravity, int iterations, int timestepfps, bool doSleep)
	{
		_world = new b2World(gravity);
		_world->SetAllowSleeping(doSleep);
		
		_contactInstance = new ContactListener();

		_iterations = iterations;
		_doSleep = doSleep;
		_timestep = 1.0f / timestepfps;
		_gravity = gravity;

		_world->SetContactListener(_contactInstance);
	}
	
	void SpriteBatch::createSprite(long long id, float x, float y, float w, float h, const sf::Texture &texture, sf::Color color, float rotation)
	{
		if (_spriteBatch.count(id) > 0)
		{
			deleteSprite(id);
		}

		sf::Sprite tmp;
		tmp.setRotation(rotation);
		tmp.setTexture(texture);
		_helperFunc.setSizeInPixel(tmp, w, h);
		tmp.setPosition(x, y);
		tmp.setColor(color);
		_spriteBatch[id] = tmp;
		_drawOrder[id] = 1;
	}


	void SpriteBatch::createPhysicSpriteBox(long long id, float x, float y, float w, float h, bool dynamic, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color, float rotation)
	{
		if (_bodyBatch.count(id) > 0)
		{
			deletePhysicSprite(id);
		}

		b2BodyDef bodyDef;
		bodyDef.position.Set(x/30.0f, y/30.0f);
		bodyDef.angle = static_cast<float32>(rotation * 3.141592653589793 / 180.0);
		if (dynamic)
			bodyDef.type = b2_dynamicBody;
		b2Body * body = _world->CreateBody(&bodyDef);


		b2PolygonShape shape;
		shape.SetAsBox((w/2.0f)/30.0f, (h/2.0f)/30.0f);
		

		b2FixtureDef fixedDef;
		fixedDef.shape = &shape;
		fixedDef.density = density;
		fixedDef.restitution = bounce;
		fixedDef.friction = friction;
		body->CreateFixture(&fixedDef);
		body->SetUserData(this);

		_bodyBatch[id] = body;

		sf::Sprite tmp;
		tmp.setRotation(rotation);
		tmp.setTexture(texture);
		_helperFunc.setSizeInPixel(tmp, w, h);
		if (dynamic)
		{
			_helperFunc.setSizeInPixel(tmp, w+0.41f, h+0.41f);
		}
		tmp.setPosition(x, y);
		tmp.setColor(color);
		_physicSpriteBatch[id] = tmp;
		_physicSpriteShapeType[id] = false;
		_doDrawPhysicsSprite[id] = true;
		//_collisionIds[id] = std::vector<long long>(6);
	}

	void SpriteBatch::createPhysicSpriteCircle(long long id, float x, float y, float diameter, bool dynamic, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color)
	{
		if (_bodyBatch.count(id) > 0)
		{
			deletePhysicSprite(id);
		}

		b2BodyDef bodyDef;
		bodyDef.position.Set(x / 30.0f, y / 30.0f);
		if (dynamic)
			bodyDef.type = b2_dynamicBody;
		b2Body * body = _world->CreateBody(&bodyDef);


		b2CircleShape shape;
		shape.m_radius = (diameter/2) / 30.0f;

		b2FixtureDef fixedDef;
		fixedDef.shape = &shape;
		fixedDef.density = density;
		fixedDef.restitution = bounce;
		fixedDef.friction = friction;
		body->CreateFixture(&fixedDef);
		body->SetUserData(this);
		
		_bodyBatch[id] = body;

		sf::Sprite tmp;
		tmp.setRotation(0);
		tmp.setTexture(texture);
		_helperFunc.setSizeInPixel(tmp, diameter, diameter);
		tmp.setPosition(x, y);
		tmp.setColor(color);
		_physicSpriteBatch[id] = tmp;
		_physicSpriteShapeType[id] = true;
		_doDrawPhysicsSprite[id] = true;
		//_collisionIds[id] = std::vector<long long>(6);
	}

	/*
	void SpriteBatch::createPhysicSpriteFixtureBoxAddToBody(long long id, float localx, float localy, float w, float h, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color, float rotation)
	{
		if (_bodyBatch.count(id) > 0)
		{



			b2PolygonShape shape;
			shape.SetAsBox(w / 2.0f/30.0f, h / 2.0f / 30.0f, b2Vec2(localx/30.0f, localy / 30.0f), rotation * 3.141592653589793 / 180.0);

			b2FixtureDef fixedDef;
			fixedDef.shape = &shape;
			fixedDef.density = density;
			fixedDef.restitution = bounce;
			fixedDef.friction = friction;
			_bodyBatch[id]->CreateFixture(&fixedDef);

		}
	}
	
	void SpriteBatch::createPhysicSpriteFixtureCircleAddToBody(long long id, float localx, float localy, float diameter, float density, float friction, float bounce, const sf::Texture &texture, sf::Color color)
	{
		if (_bodyBatch.count(id) > 0)
		{


			b2CircleShape shape;
			shape.m_radius = diameter / 2.0f / 30.0f;
			shape.m_p = b2Vec2(localx / 30.0f, localy / 30.0f);

			b2FixtureDef fixedDef;
			fixedDef.shape = &shape;
			fixedDef.density = density;
			fixedDef.restitution = bounce;
			fixedDef.friction = friction;
			_bodyBatch[id]->CreateFixture(&fixedDef);

		}
	}*/


	void SpriteBatch::createRevoluteJoint(long long firstBodyid, long long secondBodyid, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool collideConnected, float baseangle)
	{
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = _bodyBatch[firstBodyid];
		revoluteJointDef.bodyB = _bodyBatch[secondBodyid];
		localAnchorA.x /=30.0f;
		localAnchorA.y /= 30.0f;
		localAnchorB.x /= 30.0f;
		localAnchorB.y /= 30.0f;
		revoluteJointDef.localAnchorA = localAnchorA;
		revoluteJointDef.localAnchorB = localAnchorB;
		revoluteJointDef.collideConnected = collideConnected;
		revoluteJointDef.referenceAngle = static_cast<float32>(baseangle* 3.141592653589793 / 180.0);

		b2RevoluteJoint *joint = (b2RevoluteJoint*)_world->CreateJoint(&revoluteJointDef);
		_revoluteJointBatch[firstBodyid] = joint;
		_revoluteJointData[firstBodyid] = secondBodyid;
	}

	void SpriteBatch::createRevoluteJointAngLimit(long long firstBodyid, long long secondBodyid, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool collideConnected, float baseangle, float upperAngleLimit, float lowerAngleLimit)
	{
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = _bodyBatch[firstBodyid];
		revoluteJointDef.bodyB = _bodyBatch[secondBodyid];
		localAnchorA.x /= 30.0f;
		localAnchorA.y /= 30.0f;
		localAnchorB.x /= 30.0f;
		localAnchorB.y /= 30.0f;
		revoluteJointDef.localAnchorA = localAnchorA;
		revoluteJointDef.localAnchorB = localAnchorB;
		revoluteJointDef.collideConnected = collideConnected;
		revoluteJointDef.referenceAngle = static_cast<float32>(baseangle* 3.141592653589793 / 180.0);
		revoluteJointDef.enableLimit = true;
		revoluteJointDef.upperAngle = static_cast<float32>(upperAngleLimit* 3.141592653589793 / 180.0);
		revoluteJointDef.lowerAngle = static_cast<float32>(lowerAngleLimit* 3.141592653589793 / 180.0);

		b2RevoluteJoint *joint = (b2RevoluteJoint*)_world->CreateJoint(&revoluteJointDef);
		_revoluteJointBatch[firstBodyid] = joint;
		_revoluteJointData[firstBodyid] = secondBodyid;
	}

	void SpriteBatch::createRevoluteJointMotor(long long firstBodyid, long long secondBodyid, b2Vec2 localAnchorA, b2Vec2 localAnchorB, bool collideConnected, float baseangle, float MotorSpeed, float MaxMotorRotationSpeed)
	{
		b2RevoluteJointDef revoluteJointDef;
		revoluteJointDef.bodyA = _bodyBatch[firstBodyid];
		revoluteJointDef.bodyB = _bodyBatch[secondBodyid];
		localAnchorA.x /= 30.0f;
		localAnchorA.y /= 30.0f;
		localAnchorB.x /= 30.0f;
		localAnchorB.y /= 30.0f;
		revoluteJointDef.localAnchorA = localAnchorA;
		revoluteJointDef.localAnchorB = localAnchorB;
		revoluteJointDef.collideConnected = collideConnected;
		revoluteJointDef.referenceAngle = static_cast<float32>(baseangle* 3.141592653589793 / 180.0);
		revoluteJointDef.enableMotor = true;
		revoluteJointDef.motorSpeed = MotorSpeed;
		revoluteJointDef.maxMotorTorque = MaxMotorRotationSpeed;

		b2RevoluteJoint *joint = (b2RevoluteJoint*)_world->CreateJoint(&revoluteJointDef);
		_revoluteJointBatch[firstBodyid] = joint;
		_revoluteJointData[firstBodyid] = secondBodyid;
	}

	void SpriteBatch::deleteSprite(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{

			_spriteBatch.erase(id);

			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch.erase(id);
			}

			if (_spriteUserDataNum.count(id) > 0)
			{
				_spriteUserDataNum.erase(id);
			}

			if (_spriteUserDataString.count(id) > 0)
			{
				_spriteUserDataString.erase(id);
			}

			if (_spriteUserDataString2.count(id) > 0)
			{
				_spriteUserDataString2.erase(id);
			}
			_shadowOffsets.erase(id);
		}
	}

	void SpriteBatch::deleteShadow(long long id)
	{
		_shadowBatch.erase(id);
	}

	void SpriteBatch::deletePhysicSprite(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{

			_physicSpriteBatch.erase(id);

			if (_physicShadowBatch.count(id) > 0)
			{
				_physicShadowBatch.erase(id);
			}

			if (_physicSpriteUserDataNum.count(id) > 0)
			{
				_physicSpriteUserDataNum.erase(id);
			}

			if (_physicSpriteUserDataString.count(id) > 0)
			{
				_physicSpriteUserDataString.erase(id);
			}

			if (_physicSpriteUserDataString2.count(id) > 0)
			{
				_physicSpriteUserDataString2.erase(id);
			}

			if (_revoluteJointBatch.count(id) > 0)
			{
				_world->DestroyJoint(_revoluteJointBatch[id]);
				_revoluteJointBatch.erase(id);
			}
			else
			{
				for (auto x : _revoluteJointData)
				{
					if (x.second == id)
					{
						if (_revoluteJointBatch.count(x.first) > 0)
						{
							_world->DestroyJoint(_revoluteJointBatch[x.first]);
							_revoluteJointBatch.erase(x.first);
							_revoluteJointData.erase(x.first);
						}
					}
				}
			}

			_world->DestroyBody(_bodyBatch[id]);
			_bodyBatch.erase(id);
			_physicSpriteShapeType.erase(id);
			_physicShadowOffsets.erase(id);
		}

	}

	void SpriteBatch::createSpriteShadow(long long id, float shadowOffsetX, float shadowOffsetY, int alpha)
	{
		if (_spriteBatch.count(id) > 0)
		{
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch.erase(id);
			}

			sf::Sprite tmp;
			tmp.setTexture(*_spriteBatch[id].getTexture());
			tmp.setPosition(_spriteBatch[id].getPosition() + sf::Vector2f(shadowOffsetX, shadowOffsetY));
			tmp.setRotation(_spriteBatch[id].getRotation());
			tmp.setColor(sf::Color(0, 0, 0, alpha));
			_helperFunc.setSizeInPixel(tmp, _helperFunc.getSizeInPixel(_spriteBatch[id]).x, _helperFunc.getSizeInPixel(_spriteBatch[id]).y);
			_shadowBatch[id] = tmp;
			_shadowOffsets[id] = sf::Vector2f(shadowOffsetX, shadowOffsetY);
		}
		
	}

	void SpriteBatch::createPhysicSpriteShadow(long long id, float shadowOffsetX, float shadowOffsetY, int alpha)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			if (_physicShadowBatch.count(id) > 0)
			{
				_physicShadowBatch.erase(id);
			}

			sf::Sprite tmp;
			tmp.setTexture(*_physicSpriteBatch[id].getTexture());
			tmp.setPosition(_physicSpriteBatch[id].getPosition() + sf::Vector2f(shadowOffsetX, shadowOffsetY));
			tmp.setRotation(_physicSpriteBatch[id].getRotation());
			tmp.setColor(sf::Color(0, 0, 0, alpha));
			_helperFunc.setSizeInPixel(tmp, _helperFunc.getSizeInPixel(_physicSpriteBatch[id]).x, _helperFunc.getSizeInPixel(_physicSpriteBatch[id]).y);
			_physicShadowBatch[id] = tmp;
			_physicShadowOffsets[id] = sf::Vector2f(shadowOffsetX, shadowOffsetY);
		}
		
	}

	void SpriteBatch::drawPhysicSprites(Window &window)
	{
		for (auto x : _physicSpriteBatch)
		{
			window.draw(x.second);
		}
	}

	void SpriteBatch::drawShadowSprites(Window &window)
	{
		for (auto x : _shadowBatch)
		{
			window.draw(x.second);
		}
		for (auto x : _physicShadowBatch)
		{
			window.draw(x.second);
		}
	}

	void SpriteBatch::drawSprites(Window &window)
	{
		for (auto x : _spriteBatch)
		{
			window.draw(x.second);
		}
		
	}

	void SpriteBatch::drawSprite(long long id, Window &window)
	{
		window.draw(_spriteBatch[id]);
	}

	void SpriteBatch::drawPhysicSprite(long long id, Window &window)
	{
		window.draw(_physicSpriteBatch[id]);
	}

	void SpriteBatch::drawShadowSprite(long long id, Window &window)
	{
		window.draw(_shadowBatch[id]);
	}

	void SpriteBatch::drawAllFast(Window &window, bool spriteOnFront)
	{
		
		if (spriteOnFront == true)
		{
			for (auto x : _physicShadowBatch)
			{
				window.draw(x.second);
			}
			drawPhysicSprites(window);

			for (auto x : _shadowBatch)
			{
				window.draw(x.second);
			}
			drawSprites(window);

			return;
		}
		for (auto x : _shadowBatch)
		{
			window.draw(x.second);
		}
		drawSprites(window);

		for (auto x : _physicShadowBatch)
		{
			window.draw(x.second);
		}
		drawPhysicSprites(window);


	}

	void SpriteBatch::drawAll(Window &window)
	{

		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 0)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 0)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 0)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 1)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 1)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 1)
			{
				window.draw(x.second);
			}
		}


		for (auto x : _physicShadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingPhysicSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_doDrawPhysicsSprite[x.first])
			{
			window.draw(x.second);
			}
		}
		
		for (auto x : _physicSpriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingPhysicSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_doDrawPhysicsSprite[x.first])
			{
				window.draw(x.second);
			}
		}


		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 2)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 2)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 2)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 3)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 3)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 3)
			{
				window.draw(x.second);
			}
		}

	}

	void SpriteBatch::drawAllOcclusion(Window &window, sf::IntRect rect)
	{

		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 0)
			{
				if (!(_shadowBatch[x.first].getPosition().x + _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x < rect.left))
				{
					if (!(_shadowBatch[x.first].getPosition().x - _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x > rect.width))
					{
						if (!(_shadowBatch[x.first].getPosition().y + _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y < rect.top))
						{
							if (!(_shadowBatch[x.first].getPosition().y - _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 0)
			{
				if (!(_spriteBatch[x.first].getPosition().x + getSpriteSize(x.first).x < rect.left))
				{
					if (!(_spriteBatch[x.first].getPosition().x - getSpriteSize(x.first).x > rect.width))
					{
						if (!(_spriteBatch[x.first].getPosition().y + getSpriteSize(x.first).y < rect.top))
						{
							if (!(_spriteBatch[x.first].getPosition().y - getSpriteSize(x.first).y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 0)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 1)
			{
				if (!(_shadowBatch[x.first].getPosition().x + _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x < rect.left))
				{
					if (!(_shadowBatch[x.first].getPosition().x - _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x > rect.width))
					{
						if (!(_shadowBatch[x.first].getPosition().y + _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y < rect.top))
						{
							if (!(_shadowBatch[x.first].getPosition().y - _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 1)
			{
				if (!(_spriteBatch[x.first].getPosition().x + getSpriteSize(x.first).x < rect.left))
				{
					if (!(_spriteBatch[x.first].getPosition().x - getSpriteSize(x.first).x > rect.width))
					{
						if (!(_spriteBatch[x.first].getPosition().y + getSpriteSize(x.first).y < rect.top))
						{
							if (!(_spriteBatch[x.first].getPosition().y - getSpriteSize(x.first).y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 1)
			{
				window.draw(x.second);
			}
		}


		for (auto x : _physicShadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingPhysicSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_doDrawPhysicsSprite[x.first])
			{
				if (!(_physicShadowBatch[x.first].getPosition().x + _physicShadowBatch[x.first].getTexture()->getSize().x *_physicShadowBatch[x.first].getScale().x < rect.left))
				{
					if (!(_physicShadowBatch[x.first].getPosition().x - _physicShadowBatch[x.first].getTexture()->getSize().x*_physicShadowBatch[x.first].getScale().x > rect.width))
					{
						if (!(_physicShadowBatch[x.first].getPosition().y + _physicShadowBatch[x.first].getTexture()->getSize().y*_physicShadowBatch[x.first].getScale().y < rect.top))
						{
							if (!(_physicShadowBatch[x.first].getPosition().y - _physicShadowBatch[x.first].getTexture()->getSize().y*_physicShadowBatch[x.first].getScale().y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _physicSpriteBatch)
		{	
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingPhysicSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_doDrawPhysicsSprite[x.first])
			{
				if (!(_physicSpriteBatch[x.first].getPosition().x + getPhysicSpriteSize(x.first).x < rect.left))
				{
					if (!(_physicSpriteBatch[x.first].getPosition().x - getPhysicSpriteSize(x.first).x > rect.width))
					{
						if (!(_physicSpriteBatch[x.first].getPosition().y + getPhysicSpriteSize(x.first).y < rect.top))
						{
							if (!(_physicSpriteBatch[x.first].getPosition().y - getPhysicSpriteSize(x.first).y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}
		


		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 2)
			{
				if (!(_shadowBatch[x.first].getPosition().x + _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x < rect.left))
				{
					if (!(_shadowBatch[x.first].getPosition().x - _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x > rect.width))
					{
						if (!(_shadowBatch[x.first].getPosition().y + _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y < rect.top))
						{
							if (!(_shadowBatch[x.first].getPosition().y - _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 2)
			{
				if (!(_spriteBatch[x.first].getPosition().x + getSpriteSize(x.first).x < rect.left))
				{
					if (!(_spriteBatch[x.first].getPosition().x - getSpriteSize(x.first).x > rect.width))
					{
						if (!(_spriteBatch[x.first].getPosition().y + getSpriteSize(x.first).y < rect.top))
						{
							if (!(_spriteBatch[x.first].getPosition().y - getSpriteSize(x.first).y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 2)
			{
				window.draw(x.second);
			}
		}

		for (auto x : _shadowBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 3)
			{
				if (!(_shadowBatch[x.first].getPosition().x + _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x < rect.left))
				{
					if (!(_shadowBatch[x.first].getPosition().x - _shadowBatch[x.first].getTexture()->getSize().x*_spriteBatch[x.first].getScale().x > rect.width))
					{
						if (!(_shadowBatch[x.first].getPosition().y + _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y < rect.top))
						{
							if (!(_shadowBatch[x.first].getPosition().y - _shadowBatch[x.first].getTexture()->getSize().y*_spriteBatch[x.first].getScale().y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _spriteBatch)
		{
			bool Cont;
			for (long long y : _idsToIgnoreWhileDrawingSprite)
			{
				if (x.first == y)
				{
					Cont = true;
				}
			}
			if (Cont == true)
			{
				Cont = false;
				continue;
			}
			if (_drawOrder[x.first] == 3)
			{
				if (!(_spriteBatch[x.first].getPosition().x + getSpriteSize(x.first).x < rect.left))
				{
					if (!(_spriteBatch[x.first].getPosition().x - getSpriteSize(x.first).x > rect.width))
					{
						if (!(_spriteBatch[x.first].getPosition().y + getSpriteSize(x.first).y < rect.top))
						{
							if (!(_spriteBatch[x.first].getPosition().y - getSpriteSize(x.first).y > rect.height))
							{
								window.draw(x.second);
							}
						}
					}
				}
			}
		}

		for (auto x : _textBatch)
		{
			if (_drawOrderText[x.first] == 3)
			{
				window.draw(x.second);
			}
		}

	}

	void SpriteBatch::drawAllText(Window &window)
	{
		for (auto x : _textBatch)
		{

			window.draw(x.second);
			
		}
	}

	void SpriteBatch::deletePhysicShadow(long long id)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			_physicShadowBatch.erase(id);
		}
	}

	void SpriteBatch::deletePhysicSpriteRevoluteJoint(long long id)
	{

			if (_revoluteJointBatch.count(id) > 0)
			{
				_world->DestroyJoint(_revoluteJointBatch[id]);
				_revoluteJointBatch.erase(id);
				_revoluteJointData.erase(id);
			}
			else
			{
				for (auto x : _revoluteJointData)
				{
					if (x.second == id)
					{
						if (_revoluteJointBatch.count(x.first) > 0)
						{
							_world->DestroyJoint(_revoluteJointBatch[x.first]);
							_revoluteJointBatch.erase(x.first);
							_revoluteJointData.erase(x.first);
						}
					}
				}
			}
		
	}

	void SpriteBatch::setSpriteColor(long long id, sf::Color color)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setColor(color);
		}
	}

	void SpriteBatch::setSpritePosition(long long id, float x, float y)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setPosition(x,y);

			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setPosition(x, y);
			}
		}
	}

	void SpriteBatch::setSpritePosition(long long id, sf::Vector2f pos)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setPosition(pos);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setPosition(pos.x + _shadowOffsets[id].x, pos.y + _shadowOffsets[id].y);
			}
		}
	}

	void SpriteBatch::setSpriteScale(long long id, float xScale, float yScale)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setScale(xScale, yScale);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setScale(xScale, yScale);
			}
		}
	}

	void SpriteBatch::setSpriteSize(long long id, float w, float h)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_helperFunc.setSizeInPixel(_spriteBatch[id], w, h);
			if (_shadowBatch.count(id) > 0)
			{
				_helperFunc.setSizeInPixel(_shadowBatch[id], w, h);
			}
		}
	}

	void SpriteBatch::setSpriteSize(long long id, sf::Vector2f size)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_helperFunc.setSizeInPixel(_spriteBatch[id], size.x,size.y);
			if (_shadowBatch.count(id) > 0)
			{
				_helperFunc.setSizeInPixel(_shadowBatch[id], size.x, size.y);
			}
		}
	}

	void SpriteBatch::setSpriteTexture(long long id, const sf::Texture &texture)
	{
		if (_spriteBatch.count(id) > 0)
		{
			sf::Vector2f tmp;
			tmp = getSpritePosition(id);
			_spriteBatch[id].setTexture(texture,true);
			setSpriteSize(id, tmp);
		}
		
	}

	void SpriteBatch::setSpriteOrigin(long long id, sf::Vector2f origin)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setOrigin(origin);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setOrigin(origin);
			}
		}
	}

	void SpriteBatch::setSpriteOriginMiddle(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setOrigin(getSpriteTexture(id)->getSize().x / 2.0f, getSpriteTexture(id)->getSize().y / 2.0f);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setOrigin(getSpriteShadowTexture(id)->getSize().x / 2.0f, getSpriteShadowTexture(id)->getSize().y / 2.0f);
			}
		}
	}

	void SpriteBatch::setSpriteRotation(long long id, float rotation)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setRotation(rotation);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setRotation(rotation);
			}
		}
	}

	void SpriteBatch::setSpriteShadowOffset(long long id, float offsetX, float offsetY)
	{
		if (_shadowBatch.count(id) > 0)
		{
			sf::Vector2f tmp;
			tmp = _shadowBatch[id].getPosition();
			_shadowBatch[id].setPosition(tmp.x + offsetX, tmp.y + offsetY);
			_shadowOffsets[id].x = offsetX;
			_shadowOffsets[id].y = offsetY;
		}
	}

	void SpriteBatch::setSpriteShadowColor(long long id, sf::Color color)
	{
		if (_shadowBatch.count(id) > 0)
		{
			_shadowBatch[id].setColor(color);
		}
	}

	void SpriteBatch::setSpriteShadowTexture(long long id, const sf::Texture &texture)
	{
		if (_shadowBatch.count(id) > 0)
		{
			sf::Vector2f tmp;
			tmp = _helperFunc.getSizeInPixel(_shadowBatch[id]);
			_shadowBatch[id].setTexture(texture, true);
			_helperFunc.setSizeInPixel(_shadowBatch[id], tmp.x, tmp.y);
		}
	}

	void SpriteBatch::setPhysicSpriteDraw(long long id, bool draw)
	{
		_doDrawPhysicsSprite[id] = draw;
	}
	bool SpriteBatch::getPhysicSpriteDraw(long long id)
	{
		if (_doDrawPhysicsSprite.count(id) > 0)
		{
			return _doDrawPhysicsSprite[id];
		}
	}

	void SpriteBatch::restoreSpriteShadowTexture(long long id)
	{

		const sf::Texture *tmp;

		if (_spriteBatch.count(id) > 0)
		{
			tmp = getSpriteTexture(id);
			if (_shadowBatch.count(id) > 0)
			{
				setSpriteShadowTexture(id, *tmp);
			}
		}

	}

/*	void SpriteBatch::swapSprites(long long idfrom, long long idto)
	{
		if (_spriteBatch.count(idfrom) > 0)
		{
			if (_spriteBatch.count(idto) > 0)
			{
				sf::Sprite tmp;
				sf::Sprite tmp2;
				long double data;
				std::string str;
				std::string str2;
				sf::Vector2f offset;
				tmp2 = getShadowSprite(idfrom);
				tmp = getSprite(idfrom);
				data = getSpriteUserDataNum(idfrom);
				str = getSpriteUserDataStr(idfrom);
				str2 = getSpriteUserDataStr2(idfrom);
				if (_shadowOffsets.count(idfrom) > 0)
				{
					offset = _shadowOffsets[idfrom];
				}

				if (_shadowBatch.count(idto) > 0)
				{
					_shadowBatch[idfrom] = _shadowBatch[idto];
				}


				_spriteBatch[idfrom] = _spriteBatch[idto];

				if (_shadowBatch.count(idfrom) > 0)
				{
					_shadowBatch[idto] = tmp2;
				}


				_spriteBatch[idto] = tmp;
				
				if (_spriteUserDataNum.count(idto) > 0)
				{
					_spriteUserDataNum[idfrom] = _spriteUserDataNum[idto];
				}

				if (_spriteUserDataString.count(idto) > 0)
				{
					_spriteUserDataString[idfrom] = _spriteUserDataString[idto];
				}

				if (_spriteUserDataString2.count(idto) > 0)
				{
					_spriteUserDataString2[idfrom] = _spriteUserDataString2[idto];
				}
				if (_shadowOffsets.count(idto) > 0)
				{
					_shadowOffsets[idfrom] = _shadowOffsets[idto];
				}
				//---------------------------------------//

					setSpriteUserDataNum(idto, data);
				
					setSpriteUserDataStr(idto, str);

					setSpriteUserDataStr2(idto, str2);

				if (_shadowOffsets.count(idfrom) > 0)
				{
					_shadowOffsets[idto] = offset;
				}
			}
		}
	}
	*/

/*	void SpriteBatch::replaceSprites(long long idfrom, long long idto)
	{
		if (_spriteBatch.count(idfrom) > 0)
		{
			if (_spriteBatch.count(idto) > 0)
			{

				sf::Sprite tmp;
				long double data;
				std::string str;
				std::string str2;
				sf::Vector2f offset;
				tmp = getSprite(idfrom);
				data = getSpriteUserDataNum(idfrom);
				str = getSpriteUserDataStr(idfrom);
				str2 = getSpriteUserDataStr2(idfrom);
				if (_shadowOffsets.count(idfrom) > 0)
				{
					offset = _shadowOffsets[idfrom];
				}
				

				deleteSprite(idfrom);
				_spriteBatch[idto] = tmp;
				setSpriteUserDataNum(idto, data);
				setSpriteUserDataStr(idto, str);
				setSpriteUserDataStr2(idto, str2);
				createSpriteShadow(idto, offset.x, offset.y, 75);



			}
		}
	}*/

	void SpriteBatch::setSpriteUserDataNum(long long id, long double data)
	{
		_spriteUserDataNum[id] = data;
	}

	void SpriteBatch::setSpriteUserDataStr(long long id, std::string data)
	{
		_spriteUserDataString[id] = data;
	}

	void SpriteBatch::setSpriteUserDataStr2(long long id, std::string data)
	{
		_spriteUserDataString2[id] = data;
	}

	sf::Color SpriteBatch::getSpriteColor(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id].getColor();
		}
	}

	sf::Vector2f SpriteBatch::getSpritePosition(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id].getPosition();
		}
	}

	sf::Vector2f SpriteBatch::getSpriteScale(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id].getScale();
		}
	}

	sf::Vector2f SpriteBatch::getSpriteSize(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _helperFunc.getSizeInPixel(_spriteBatch[id]);
		}
	}

	const sf::Texture *SpriteBatch::getSpriteTexture(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id].getTexture();
		}
	}

	sf::Vector2f SpriteBatch::getSpriteOrigin(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id].getOrigin();
		}
	}

	sf::Sprite &SpriteBatch::getSprite(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id];
		}
	}

	sf::Sprite &SpriteBatch::getShadowSprite(long long id)
	{
		if (_shadowBatch.count(id) > 0)
		{
			return _shadowBatch[id];
		}
	}

	float SpriteBatch::getSpriteRotation(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _spriteBatch[id].getRotation();
		}
	}


	sf::Color SpriteBatch::getSpriteShadowColor(long long id)
	{
		if (_shadowBatch.count(id) > 0)
		{
			return _shadowBatch[id].getColor();
		}
	}

	const sf::Texture *SpriteBatch::getSpriteShadowTexture(long long id)
	{
		if (_shadowBatch.count(id) > 0)
		{
			return _shadowBatch[id].getTexture();
		}
	}

	long double SpriteBatch::getSpriteUserDataNum(long long id)
	{
		if (_spriteUserDataNum.count(id) > 0)
		{
			return _spriteUserDataNum[id];
		}
	}

	std::string SpriteBatch::getSpriteUserDataStr(long long id)
	{
		if (_spriteUserDataString.count(id) > 0)
		{
			return _spriteUserDataString[id];
		}
		return "";
	}

	std::string SpriteBatch::getSpriteUserDataStr2(long long id)
	{
		if (_spriteUserDataString.count(id) > 0)
		{
			return _spriteUserDataString[id];
		}
		return "";
	}

	long long SpriteBatch::getSpriteCountUserDataNum(long double data)
	{
		long long count=0;
		for (auto x : _spriteUserDataNum)
		{
			if (x.second == data)
			{
				count++;
			}
		}
		return count;
	}

	long long SpriteBatch::getSpriteCountUserDataStr(std::string data)
	{
		long long count = 0;
		for (auto x : _spriteUserDataString)
		{
			if (x.second == data)
			{
				count++;
			}
		}
		return count;
	}

	long long SpriteBatch::getSpriteCountUserDataStr2(std::string data)
	{
		long long count = 0;
		for (auto x : _spriteUserDataString2)
		{
			if (x.second == data)
			{
				count++;
			}
		}
		return count;
	}

	void SpriteBatch::deleteSpriteUserDataNum(long long id)
	{
		if (_spriteUserDataNum.count(id) > 0)
		{
			_spriteUserDataNum.erase(id);
		}
	}

	void SpriteBatch::deleteSpriteUserDataStr(long long id)
	{
		if (_spriteUserDataString.count(id) > 0)
		{
			_spriteUserDataString.erase(id);
		}
	}

	void SpriteBatch::deleteSpriteUserDataStr2(long long id)
	{
		if (_spriteUserDataString2.count(id) > 0)
		{
			_spriteUserDataString2.erase(id);
		}
	}

	bool SpriteBatch::isExistingSprite(long long id)
	{
		if (_spriteBatch.count(id)>0)
		{
			return true;
		}
		return false;
	}

	void SpriteBatch::addSpritePosition(long long id, sf::Vector2f pos)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setPosition(_spriteBatch[id].getPosition() + pos);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setPosition(_shadowBatch[id].getPosition() + pos);
			}
		}
	}

	void SpriteBatch::addSpriteRotation(long long id, float rotation)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_spriteBatch[id].setRotation(_spriteBatch[id].getRotation() + rotation);
			if (_shadowBatch.count(id) > 0)
			{
				_shadowBatch[id].setRotation(_spriteBatch[id].getRotation() + rotation);
			}
		}
	}

	void SpriteBatch::setSpriteDrawOrder(long long id, int order)
	{
		if (_spriteBatch.count(id) > 0)
		{
			_drawOrder[id] = order;
		}
	}

	int SpriteBatch::getSpriteDrawOrder(long long id)
	{
		if (_spriteBatch.count(id) > 0)
		{
			return _drawOrder[id];
		}
	}

	bool SpriteBatch::testPointSprite(float x, float y)
	{
		for (auto x2 : _spriteBatch)
		{
			if (x > getSpritePosition(x2.first).x){
				if (y > getSpritePosition(x2.first).y)
				{
					if (x < getSpritePosition(x2.first).x + getSpriteSize(x2.first).x)
					{
						if (y < getSpritePosition(x2.first).x + getSpriteSize(x2.first).y)
						{
							return true;
						}
					}
				}
			}
		}
		return false;
	}

	bool SpriteBatch::testPointSpriteId(long long id,float x, float y)
	{

			if (x > getSpritePosition(id).x)
			{
				if (y > getSpritePosition(id).y)
				{
					if (x < getSpritePosition(id).x + getSpriteSize(id).x)
					{
						if (y < getSpritePosition(id).y + getSpriteSize(id).y)
						{
							return true;
						}
					}
				}
			}
		
		return false;
	}

	long long SpriteBatch::testPointSpriteId(float x, float y)
	{
		for (auto x2 : _spriteBatch)
		{
			if (testPointSprite(x ,y))
			{
				return x2.first;
			}
		}
		
	}

	std::vector<long long> SpriteBatch::testPointSpriteIdAll(float x, float y)
	{
		std::vector<long long> Ids;
		for (auto x2 : _spriteBatch)
		{
			if (testPointSpriteId(x2.first,x, y))
			{
				Ids.push_back(x2.first);
			}
		}
		return Ids;

	}
	//---------------------------------------------------------------
	void SpriteBatch::createText(long long id, float x, float y, float wScale, float hScale, int characterSize, sf::Font &font, std::string text, sf::Color color, float rotation)
	{
		sf::Text tmp;
		tmp.setPosition(x, y);
		tmp.setScale(wScale, hScale);
		tmp.setCharacterSize(characterSize);
		tmp.setFont(font);
		tmp.setString(text);
		tmp.setColor(color);
		tmp.setRotation(rotation);
		_textBatch[id] = tmp;
		_drawOrderText[id] = 1;
	}

	void SpriteBatch::setText(long long id, std::string text)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setString(text);
		}
	}

	void SpriteBatch::setTextStyle(long long id, sf::Uint32 style)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setStyle(style);
		}
	}

	void SpriteBatch::setTextPosition(long long id, sf::Vector2f pos)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setPosition(pos);
		}
	}

	void SpriteBatch::setTextRotaion(long long id, float rotation)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setRotation(rotation);
		}
	}

	void SpriteBatch::setTextScale(long long id, sf::Vector2f scale)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setScale(scale);
		}
	}

	void SpriteBatch::setTextCharacterSize(long long id, int size)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setCharacterSize(size);
		}
	}

	void SpriteBatch::addTextPosition(long long id, sf::Vector2f pos)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setPosition(_textBatch[id].getPosition() + pos);
		}
	}

	void SpriteBatch::setTextColor(long long id, sf::Color color)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setColor(color);
		}
	}

	void SpriteBatch::setTextOrigin(long long id, sf::Vector2f origin)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setOrigin(origin);
		}
	}

	sf::Vector2f SpriteBatch::getTextPosition(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getPosition();
		}
	}

	sf::Text &SpriteBatch::getText(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id];
		}
	}

	sf::Vector2f SpriteBatch::getTextOrigin(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getOrigin();
		}
	}

	sf::Color SpriteBatch::getTextColor(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getColor();
		}
	}

	int SpriteBatch::getTextCharacterSize(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getCharacterSize();
		}
	}

	sf::Vector2f SpriteBatch::getTextScale(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getScale();
		}
	}

	float SpriteBatch::getTextRotation(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getRotation();
		}
	}

	sf::Uint32 SpriteBatch::getTextStyle(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getStyle();
		}
	}

	std::string SpriteBatch::getTextString(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getString();
		}
	}

	const sf::Font *SpriteBatch::getTextFont(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _textBatch[id].getFont();
		}
	}

	void SpriteBatch::setTextFont(long long id, sf::Font &font)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch[id].setFont(font);
		}
	}

	void SpriteBatch::setTextDrawOrder(long long id, int order)
	{
		if (_textBatch.count(id) > 0)
		{
			_drawOrderText[id] = order;
		}
	}

	int SpriteBatch::getTextDrawOrder(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			return _drawOrderText[id];
		}
	}
	void SpriteBatch::deleteText(long long id)
	{
		if (_textBatch.count(id) > 0)
		{
			_textBatch.erase(id);
		}
	}
	//---------------------------------------------------------------
	void SpriteBatch::setPhysicSpriteColor(long long id, sf::Color color)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			_physicSpriteBatch[id].setColor(color);
		}
	}

	void SpriteBatch::setPhysicSpritePosition(long long id, float x, float y)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setPosition(x+_physicShadowOffsets[id].x, y + _physicShadowOffsets[id].y);
				}
				_physicSpriteBatch[id].setPosition(x, y);
				
			}
			_bodyBatch[id]->SetTransform(b2Vec2(x / 30, y / 30), _bodyBatch[id]->GetAngle());
		}
	}

	void SpriteBatch::setPhysicSpritePosition(long long id, sf::Vector2f pos)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setPosition(pos.x + _physicShadowOffsets[id].x, pos.y + _physicShadowOffsets[id].y);
				}
				_physicSpriteBatch[id].setPosition(pos);
				
			}
			_bodyBatch[id]->SetTransform(b2Vec2(pos.x / 30, pos.y / 30), _bodyBatch[id]->GetAngle());
		}
	}

	void SpriteBatch::setPhysicSpritePosition(long long id, b2Vec2 pos)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setPosition(pos.x+ _physicShadowOffsets[id].x,pos.y+ _physicShadowOffsets[id].y);
				}
				_physicSpriteBatch[id].setPosition(pos.x,pos.y);
				
			}
			_bodyBatch[id]->SetTransform(b2Vec2(pos.x / 30,pos.y / 30), _bodyBatch[id]->GetAngle());
		}
	}

	void SpriteBatch::setPhysicSpriteSizeBox(long long id, float w, float h)
	{
		float density = 0;
		float bounce = 0;
		float friction = 0;
		const sf::Texture *texture;
		sf::Color color;
		float x = 0;
		float y = 0;
		float rotation = 0;
		sf::Vector2f offset;
		const sf::Texture *shadowTexture = nullptr;
		bool shadow = false;
		float shadowalpha = 255;


		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteShapeType[id] == true)
			{
				return;
			}
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					shadow = true;
					offset = _physicShadowOffsets[id];
					shadowalpha = _physicShadowBatch[id].getColor().a;
					shadowTexture = getPhysicSpriteShadowTexture(id);
					_helperFunc.setSizeInPixel(_physicShadowBatch[id], w, h);
				}
				_helperFunc.setSizeInPixel(_physicSpriteBatch[id], w, h);
			}

			x = _bodyBatch[id]->GetPosition().x*30.0f;
		    y = _bodyBatch[id]->GetPosition().y*30.0f;
			color = getPhysicSpriteColor(id);
			texture = getPhysicSpriteTexture(id);
			friction = _bodyBatch[id]->GetFixtureList()->GetFriction();
			bounce = _bodyBatch[id]->GetFixtureList()->GetRestitution();
			density = _bodyBatch[id]->GetFixtureList()->GetDensity();
			rotation = _physicSpriteBatch[id].getRotation();
			deletePhysicSprite(id);

			bool type;

			type = isPhysicSpriteDynamic(id);

			createPhysicSpriteBox(id, x, y, w, h, type, density, friction, bounce, *texture, color, rotation);
			if (shadow)
			{
				createPhysicSpriteShadow(id, offset.x, offset.y, shadowalpha);
				if(shadowTexture != nullptr)
				setPhysicSpriteShadowTexture(id, *shadowTexture);
			}
		}
	}

	void SpriteBatch::setPhysicSpriteSizeCircle(long long id, float diameter)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteShapeType[id] == false)
			{
				return;
			}
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					_helperFunc.setSizeInPixel(_physicShadowBatch[id], diameter, diameter);
				}
				_helperFunc.setSizeInPixel(_physicSpriteBatch[id], diameter, diameter);
			}
			_bodyBatch[id]->GetFixtureList()->GetShape()->m_radius = (diameter / 2) /30;
		}
	}

	void SpriteBatch::setPhysicSpriteTexture(long long id, const sf::Texture &texture)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			sf::Vector2f tmp = getPhysicSpriteSize(id);
			_physicSpriteBatch[id].setTexture(texture, true);
			setPhysicSpriteSizeBox(id, tmp.x, tmp.x);
			setPhysicSpriteSizeCircle(id, tmp.x);
		}
	}

	void SpriteBatch::setPhysicSpriteOrigin(long long id, sf::Vector2f origin)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			_physicSpriteBatch[id].setOrigin(origin);
			if (_physicShadowBatch.count(id) > 0)
			{
				_physicShadowBatch[id].setOrigin(origin);
			}
		}
	}

	void SpriteBatch::setPhysicSpriteOriginMiddle(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			_physicSpriteBatch[id].setOrigin(getPhysicSpriteTexture(id)->getSize().x / 2.0f, getPhysicSpriteTexture(id)->getSize().y / 2.0f);
			if (_physicShadowBatch.count(id) > 0)
			{
				_physicShadowBatch[id].setOrigin(getPhysicSpriteShadowTexture(id)->getSize().x / 2.0f, getPhysicSpriteShadowTexture(id)->getSize().y / 2.0f);
			}
		}
	}

	void SpriteBatch::setPhysicSpriteRotation(long long id, float rotation)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				_physicSpriteBatch[id].setRotation(rotation);
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setRotation(rotation);
				}
			}

			_bodyBatch[id]->SetTransform(_bodyBatch[id]->GetPosition(), static_cast<float32>(rotation* 3.141592653589793 / 180.0));
		}
	}

	void SpriteBatch::setPhysicSpriteShadowOffset(long long id, float offsetX, float offsetY)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			sf::Vector2f tmp;
			tmp = _physicShadowBatch[id].getPosition();
			_physicShadowBatch[id].setPosition(tmp.x + offsetX, tmp.y + offsetY);
			_physicShadowOffsets[id].x;
			_physicShadowOffsets[id].y;
		}
	}

	void SpriteBatch::setPhysicSpriteShadowColor(long long id, sf::Color color)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			_physicShadowBatch[id].setColor(color);
		}
	}

	void SpriteBatch::setPhysicSpriteShadowTexture(long long id, const sf::Texture &texture)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			sf::Vector2f tmp;
			tmp = _helperFunc.getSizeInPixel(_physicShadowBatch[id]);
			_physicShadowBatch[id].setTexture(texture, true);
			_helperFunc.setSizeInPixel(_physicShadowBatch[id],tmp.x,tmp.y);
		}
	}

	void SpriteBatch::restorePhysicSpriteShadowTexture(long long id)
	{
		const sf::Texture *tmp;

		if (_physicSpriteBatch.count(id) > 0)
		{
			tmp = getPhysicSpriteTexture(id);
			if (_physicShadowBatch.count(id) > 0)
			{
				setPhysicSpriteShadowTexture(id, *tmp);
			}
		}

	}

/*	void SpriteBatch::swapPhysicSprites(long long idfrom, long long idto)
	{
		if (_physicSpriteBatch.count(idfrom) > 0)
		{
			if (_physicSpriteBatch.count(idto) > 0)
			{
				if (_bodyBatch.count(idfrom) > 0)
				{
					if (_bodyBatch.count(idto) > 0)
					{
						sf::Sprite tmp;
						sf::Sprite tmp2;
						long double data;
						std::string str;
						std::string str2;
						sf::Vector2f offset;
						bool shape;
						b2Body * body;
						tmp2 = getPhyiscShadowSprite(idfrom);
						tmp = getPhysicSprite(idfrom);
						data = getPhysicSpriteUserDataNum(idfrom);
						str = getPhysicSpriteUserDataStr(idfrom);
						str2 = getPhysicSpriteUserDataStr2(idfrom);
						body = getPhysicSpriteBody(idfrom);
						shape = _physicSpriteShapeType[idfrom];
						if (_physicShadowOffsets.count(idfrom) > 0)
						{
							offset = _physicShadowOffsets[idfrom];
						}

						deletePhysicSpriteRevoluteJoint(idfrom);
						deletePhysicSpriteRevoluteJoint(idto);

						if (_physicSpriteUserDataNum.count(idfrom) > 0)
						{
							_physicSpriteUserDataNum[idto] = data;
						}

						if (_physicSpriteUserDataString.count(idfrom) > 0)
						{
							_physicSpriteUserDataString[idto] = str;
						}

						if (_physicSpriteUserDataString2.count(idfrom) > 0)
						{
							_physicSpriteUserDataString2[idto] = str2;
						}

						if (_physicShadowOffsets.count(idfrom) > 0)
						{
							_physicShadowOffsets[idto] = offset;
						}


						if (_physicShadowBatch.count(idto) > 0)
						{
							_physicShadowBatch[idfrom] = _physicShadowBatch[idto];
						}

						_physicSpriteBatch[idfrom] = _physicSpriteBatch[idto];

						if (_physicShadowBatch.count(idfrom) > 0)
						{
							_physicShadowBatch[idto] = tmp2;
						}

						_physicSpriteBatch[idto] = tmp;

						if (_physicSpriteUserDataNum.count(idto) > 0)
						{
							_physicSpriteUserDataNum[idfrom] = _physicSpriteUserDataNum[idto];
						}

						if (_physicSpriteUserDataString.count(idto) > 0)
						{
							_physicSpriteUserDataString[idfrom] = _physicSpriteUserDataString[idto];
						}

						if (_physicSpriteUserDataString2.count(idto) > 0)
						{
							_physicSpriteUserDataString2[idfrom] = _physicSpriteUserDataString2[idto];
						}

						if (_physicShadowOffsets.count(idto) > 0)
						{
							_physicShadowOffsets[idfrom] = _physicShadowOffsets[idto];
						}

						//---------------------------------------//

						_bodyBatch[idfrom] = _bodyBatch[idto];
						_bodyBatch[idto] = body;
						_physicSpriteShapeType[idfrom] = _physicSpriteShapeType[idto];
						_physicSpriteShapeType[idto] = shape;
					}
				}
			}
		}
	}*/

/*	void SpriteBatch::replacePhysicSprites(long long idfrom, long long idto)
	{
		if (_physicSpriteBatch.count(idfrom) > 0)
		{

			if (_physicSpriteBatch.count(idto) > 0)
			{
				if (_bodyBatch.count(idfrom) > 0)
				{
					if (_bodyBatch.count(idto) > 0)
					{
						sf::Sprite tmp;
						sf::Sprite tmp2;
						long double data;
						std::string str;
						std::string str2;
						b2Body * body;
						tmp2 = getPhyiscShadowSprite(idfrom);
						tmp = getPhysicSprite(idfrom);
						data = getPhysicSpriteUserDataNum(idfrom);
						str = getPhysicSpriteUserDataStr(idfrom);
						str2 = getPhysicSpriteUserDataStr2(idfrom);
						body = getPhysicSpriteBody(idfrom);

						if (_physicShadowBatch.count(idfrom) > 0)
						{
							_physicShadowBatch[idto] = tmp2;
						}

						deletePhysicSpriteRevoluteJoint(idto);
						
						deletePhysicSprite(idfrom);
						
						setPhysicSpriteUserDataNum(idto,data);
						setPhysicSpriteUserDataStr(idto,str);
						setPhysicSpriteUserDataStr2(idto, str2);

						_physicSpriteBatch[idto] = tmp;


						_bodyBatch[idto] = body;

					}
				}
			}
		}
	}*/

	void SpriteBatch::setPhysicSpriteUserDataNum(long long id, long double data)
	{
		_physicSpriteUserDataNum[id] = data;
	}

	void SpriteBatch::setPhysicSpriteUserDataStr(long long id, std::string data)
	{
		_physicSpriteUserDataString[id] = data;
	}

	void SpriteBatch::setPhysicSpriteUserDataStr2(long long id, std::string data)
	{
		_physicSpriteUserDataString2[id] = data;
	}

	sf::Color SpriteBatch::getPhysicSpriteColor(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id].getColor();
		}
	}

	sf::Vector2f SpriteBatch::getPhysicSpritePosition(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id].getPosition();
		}
	}

	sf::Vector2f SpriteBatch::getPhysicSpriteScale(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id].getScale();
		}
	}

	sf::Vector2f SpriteBatch::getPhysicSpriteSize(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _helperFunc.getSizeInPixel(_physicSpriteBatch[id]);
		}
	}

	const sf::Texture *SpriteBatch::getPhysicSpriteTexture(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id].getTexture();
		}
	}

	b2Body *SpriteBatch::getPhysicSpriteBody(long long id)
	{
		if (_bodyBatch.count(id) > 0)
		{
			return _bodyBatch[id];
		}
	}

	sf::Sprite &SpriteBatch::getPhysicSprite(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id];
		}
	}

	sf::Sprite &SpriteBatch::getPhyiscShadowSprite(long long id)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			return _physicShadowBatch[id];
		}
	}

	float SpriteBatch::getPhysicSpriteRotation(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id].getRotation();
		}
	}

	sf::Color SpriteBatch::getPhysicSpriteShadowColor(long long id)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			return _physicShadowBatch[id].getColor();
		}
	}

	const sf::Texture *SpriteBatch::getPhysicSpriteShadowTexture(long long id)
	{
		if (_physicShadowBatch.count(id) > 0)
		{
			return _physicShadowBatch[id].getTexture();
		}
	}

	sf::Vector2f SpriteBatch::getPhysicSpriteOrigin(long long id)
	{
		if (_physicSpriteBatch.count(id) > 0)
		{
			return _physicSpriteBatch[id].getOrigin();
		}
	}

	long double SpriteBatch::getPhysicSpriteUserDataNum(long long id)
	{
		if (_physicSpriteUserDataNum.count(id) > 0)
		{
			return _physicSpriteUserDataNum[id];
		}
	}

	std::string SpriteBatch::getPhysicSpriteUserDataStr(long long id)
	{
		if (_physicSpriteUserDataString.count(id) > 0)
		{
			return _physicSpriteUserDataString[id];
		}
		return "";
	}

	std::string SpriteBatch::getPhysicSpriteUserDataStr2(long long id)
	{
		if (_physicSpriteUserDataString2.count(id) > 0)
		{
			return _physicSpriteUserDataString2[id];
		}
		return "";
	}


	long long SpriteBatch::getPhysicSpriteCountUserDataNum(long double data)
	{
		long long count = 0;
		for (auto x : _physicSpriteUserDataNum)
		{
			if (x.second == data)
			{
				count++;
			}
		}
		return count;
	}

	long long SpriteBatch::getPhysicSpriteCountUserDataStr(std::string data)
	{
		long long count = 0;
		for (auto x : _physicSpriteUserDataString)
		{
			if (x.second == data)
			{
				count++;
			}
		}
		return count;
	}

	long long SpriteBatch::getPhysicSpriteCountUserDataStr2(std::string data)
	{
		long long count = 0;
		for (auto x : _physicSpriteUserDataString2)
		{
			if (x.second == data)
			{
				count++;
			}
		}
		return count;
	}

	void SpriteBatch::freezePhysicSprite(long long id, bool freezed)
	{
		if (_bodyBatch.count(id) > 0)
		{

			if (freezed)
			{
				_bodyBatch[id]->SetType(b2_staticBody);
			}
			else
			{
				_bodyBatch[id]->SetType(b2_dynamicBody);
			}
		}
	}

	bool SpriteBatch::isCollidingPhysicSprite(long long id)
	{
		//std::cout << _collisionIds[id].size();
		if (_collisionIds[id].size() > 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	std::vector<long long> SpriteBatch::getAllCollidersIdPhysicSprite(long long id)
	{
		return _collisionIds[id];
	}

	bool SpriteBatch::isCollidingWithPhysicSprite(long long id, long long collidingId)
	{
		for (long long x : _collisionIds[id])
		{
			if (x == collidingId)
			{
				return true;
			}
		}
		return false;
	}

	bool SpriteBatch::testPointPhysicSprite(float x, float y)
	{
		bool flag;
		b2Vec2 tmp = b2Vec2(x / 30.0f, y / 30.0f);
		for (auto x : _bodyBatch)
		{
			
			flag = x.second->GetFixtureList()->TestPoint(tmp);
			if (flag)
			{
				break;
			}

		}
		return flag;
	}

	long long SpriteBatch::testPointIdPhyiscSprite(float x, float y)
	{
		long long id;
		b2Vec2 tmp = b2Vec2(x/30.0f, y / 30.0f);
		for (auto x : _bodyBatch)
		{
			if (x.second->GetFixtureList()->TestPoint(tmp))
			{
				id = x.first;
				break;
			}

		}
		return id;
	}

	std::vector<long long> SpriteBatch::testPointIdPhyiscSpriteAll(float x, float y)
	{
		std::vector<long long> Ids;
		long long id = 0;
		b2Vec2 tmp = b2Vec2(x / 30.0f, y / 30.0f);
		for (auto x : _bodyBatch)
		{
			if (x.second->GetFixtureList()->TestPoint(tmp))
			{
				Ids.push_back(x.first);
				
			}

		}
		return Ids;
	}

	void SpriteBatch::setPhysicSpriteVelocity(long long id, b2Vec2 velocity)
	{
		if (_bodyBatch.count(id) > 0)
		{
			velocity.x /= 30.0f;
			velocity.y /= 30.0f;
			_bodyBatch[id]->SetLinearVelocity(velocity);
		}
	}

	void SpriteBatch::setPhysicSpriteAngularVelocity(long long id, float angVelocity)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->SetAngularVelocity(static_cast<float32>(angVelocity* 3.141592653589793 / 180.0));
		}
	}

	void SpriteBatch::addPhysicSpriteVelocity(long long id, b2Vec2 velocity)
	{
		if (_bodyBatch.count(id) > 0)
		{
			b2Vec2 tmp = _bodyBatch[id]->GetLinearVelocity();
			tmp.x /= 30.0f;
			tmp.y /= 30.0f;
			velocity.x /= 30.0f;
			velocity.y /= 30.0f;
			_bodyBatch[id]->SetLinearVelocity(tmp+velocity);
		}
	}

	void SpriteBatch::addPhysicSpriteAngularVelocity(long long id, float angVelocity)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->SetAngularVelocity(static_cast<float32>(_bodyBatch[id]->GetAngularVelocity()*180 / 3.141592653589793 + angVelocity* 3.141592653589793 / 180.0));
		}
	}

	void SpriteBatch::addPhysicSpritePosition(long long id, sf::Vector2f pos)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setPosition(_physicShadowBatch[id].getPosition() + pos);
				}
				_physicSpriteBatch[id].setPosition(_physicSpriteBatch[id].getPosition() + pos);
			}
			pos.x /= 30.0f;
			pos.y /= 30.0f;
			_bodyBatch[id]->SetTransform(_bodyBatch[id]->GetPosition() + b2Vec2(pos.x, pos.y), _bodyBatch[id]->GetAngle());
		}
	}

	void SpriteBatch::addPhysicSpriteRotation(long long id, float rotation)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setRotation(static_cast<float32>(_physicShadowBatch[id].getRotation() + rotation* 3.141592653589793 / 180.0));
				}
				_physicSpriteBatch[id].setRotation(static_cast<float32>(_physicSpriteBatch[id].getRotation() + rotation* 3.141592653589793 / 180.0));
			}
			_bodyBatch[id]->SetTransform(_bodyBatch[id]->GetPosition(), static_cast<float32>(rotation* 3.141592653589793 / 180.0));
		}
	}

	void SpriteBatch::setPhysicSpriteFriction(long long id, float friction)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->GetFixtureList()->SetFriction(friction);
		}
	}

	void SpriteBatch::setPhysicSpriteDensity(long long id, float density)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->GetFixtureList()->SetDensity(density);
		}
	}

	void SpriteBatch::setPhysicSpriteMass(long long id, float mass)
	{
		b2MassData *data;
		data->mass = mass;
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->SetMassData(data);
		}
	}

	void SpriteBatch::setPhysicSpriteBounce(long long id, float bounce)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->GetFixtureList()->SetRestitution(bounce);
		}
	}

	void SpriteBatch::updatePhysicSprite(long long id)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				_physicSpriteBatch[id].setPosition(_bodyBatch[id]->GetPosition().x*30.0f, _bodyBatch[id]->GetPosition().y*30.0f);

				setPhysicSpriteOriginMiddle(id);
				if (_physicShadowBatch.count(id) > 0)
				{
					_physicShadowBatch[id].setPosition(_bodyBatch[id]->GetPosition().x*30.0f+_physicShadowOffsets[id].x, _bodyBatch[id]->GetPosition().y*30.0f + _physicShadowOffsets[id].y);
					_physicShadowBatch[id].setRotation(static_cast<float>(_bodyBatch[id]->GetAngle() *180.0 / 3.14159265));
				}
				_physicSpriteBatch[id].setRotation(static_cast<float>(_bodyBatch[id]->GetAngle() *180.0 / 3.14159265));
			}
		}
	}

	void SpriteBatch::updateAllPhysicSprites()
	{
		for (auto x : _bodyBatch)
		{
			updatePhysicSprite(x.first);
		}
	}

	void SpriteBatch::deletePhysicSpriteUserDataNum(long long id)
	{
		_physicSpriteUserDataNum.erase(id);
	}

	void SpriteBatch::deletePhysicSpriteUserDataStr(long long id)
	{
		_physicSpriteUserDataString.erase(id);
	}

	void SpriteBatch::deletePhysicSpriteUserDataStr2(long long id)
	{
		_physicSpriteUserDataString2.erase(id);
	}

	void SpriteBatch::worldStep()
	{
		_world->Step(_timestep,_iterations,_iterations);
	}

	std::unordered_map<long long, sf::Sprite>& SpriteBatch::getSpriteShadowBatch()
	{
		return _shadowBatch;
	}

	std::unordered_map<long long, sf::Sprite>& SpriteBatch::getSpriteBatch()
	{
		return _spriteBatch;
	}

	std::unordered_map<long long, sf::Sprite>& SpriteBatch::getPhysicSpriteShadowBatch()
	{
		return _physicShadowBatch;
	}

	std::unordered_map<long long, sf::Sprite>& SpriteBatch::getPhysicSpriteBatch()
	{
		return _physicSpriteBatch;
	}

	std::unordered_map<long long, b2Body*>& SpriteBatch::getBodyBatch()
	{
		return _bodyBatch;
	}

	std::unordered_map<long long, b2RevoluteJoint*>& SpriteBatch::getRevoluteJointBatch()
	{
		return _revoluteJointBatch;
	}

	std::unordered_map<long long, bool>& SpriteBatch::getPhysicSpriteShapeTypes()
	{
		return _physicSpriteShapeType;
	}

	std::vector<long long> &SpriteBatch::getIdsToIgnoreWhileDrawingSpritesArray()
	{
		return _idsToIgnoreWhileDrawingSprite;
	}
	std::vector<long long> &SpriteBatch::getIdsToIgnoreWhileDrawingPhysicSpritesArray()
	{
		return _idsToIgnoreWhileDrawingPhysicSprite;
	}

	void SpriteBatch::setIdsToIgnoreWhileDrawingSprites(std::vector<long long> table)
	{
		_idsToIgnoreWhileDrawingSprite = table;
	}

	void SpriteBatch::setIdsToIgnoreWhileDrawingPhysicSprites(std::vector<long long> table)
	{
		_idsToIgnoreWhileDrawingPhysicSprite = table;
	}


	std::unordered_map<long long, std::vector<long long>>& SpriteBatch::getPhysicSpriteCollisionIdsBatch()
	{
		return _collisionIds;
	}

	b2World *SpriteBatch::getWorld()
	{
		return _world;
	}

	bool SpriteBatch::isPhysicSpriteDynamic(long long id)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_bodyBatch[id]->GetType() == b2_dynamicBody)
			{
				return true;
			}
			else
			{
				return false;
			}
			

		}
		return false;
	}

	bool SpriteBatch::getPhysicSpriteShapeType(long long id)
	{
		if (_physicSpriteShapeType.count(id) > 0)
		{
			return _physicSpriteShapeType[id];
		}
	}

	void SpriteBatch::applyForcePhysicSprite(long long id, b2Vec2 direction, b2Vec2 point)
	{
		if (_bodyBatch.count(id) > 0)
		{
			point.x /= 30.0f;
			point.y /= 30.0f;
			direction.x /= 30.0f;
			direction.y /= 30.0f;
			_bodyBatch[id]->ApplyForce(direction, point, true);
		}
	}

	void SpriteBatch::applyImpusePhysicSprite(long long id, b2Vec2 direction, b2Vec2 point)
	{
		if (_bodyBatch.count(id) > 0)
		{
			point.x /= 30.0f;
			point.y /= 30.0f;
			direction.x /= 30.0f;
			direction.y /= 30.0f;
			_bodyBatch[id]->ApplyLinearImpulse(direction, point, true);
		}
	}

	void SpriteBatch::applyAngularForcePhysicSprite(long long id, float force)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->ApplyTorque(static_cast<float32>(force* 3.141592653589793 / 180.0), true);
		}
	}

	void SpriteBatch::applyAngularImpusePhysicSprite(long long id, float impulse)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->ApplyAngularImpulse(static_cast<float32>(impulse* 3.141592653589793 / 180.0), true);
		}
	}

	b2Vec2 SpriteBatch::getPhysicSpriteWorldPoint(long long id, b2Vec2 localPoint)
	{
		if (_bodyBatch.count(id) > 0)
		{
			localPoint.x /= 30.0f;
			localPoint.y /= 30.0f;

			b2Vec2 tmp = _bodyBatch[id]->GetWorldPoint(localPoint);
			tmp.x *= 30.0f;
			tmp.y *= 30.0f;

			return tmp;
		}
	}

	b2Vec2 SpriteBatch::getPhysicSpriteLocalPoint(long long id, b2Vec2 worldPoint)
	{
		if (_bodyBatch.count(id) > 0)
		{
			worldPoint.x /= 30.0f;
			worldPoint.y /= 30.0f;

			b2Vec2 tmp = _bodyBatch[id]->GetLocalPoint(worldPoint);
			tmp.x *= 30.0f;
			tmp.y *= 30.0f;

			return tmp;
		}
	}

	bool SpriteBatch::isExistingPhysicSprite(long long id)
	{
		if (_bodyBatch.count(id) > 0)
		{
			if (_physicSpriteBatch.count(id) > 0)
			{
				return true;
			}
		}
		return false;
	}

	void SpriteBatch::setSensorPhysicSprite(long long id, bool sensor)
	{
		if (_bodyBatch.count(id) > 0)
		{
			_bodyBatch[id]->GetFixtureList()->SetSensor(sensor);
		}
	}

	bool SpriteBatch::isCollidingPhysicSpriteExceptIds(long long id, std::vector<long long> idsToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id : _collisionIds[id])
				{
					for (long long data : idsToExcept)
					{
						if (id != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(idsToExcept.size()))
					{
						return true;
					}
					count = 0;
				}
				
			}
		}
		return false;
	}

	bool SpriteBatch::isCollidingPhysicSpriteExceptUserDataNum(long long id, std::vector<long double> dataToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id : _collisionIds[id])
				{
					for (long double data : dataToExcept)
					{
						if (getPhysicSpriteUserDataNum(id) != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(dataToExcept.size()))
					{
						return true;
					}
					count = 0;
				}

			}
		}
		return false;
	}

	bool SpriteBatch::isCollidingPhysicSpriteExceptUserDataStr(long long id, std::vector<std::string> dataToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id2 : _collisionIds[id])
				{
					for (std::string data : dataToExcept)
					{
						if (getPhysicSpriteUserDataStr(id2) != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(dataToExcept.size()))
					{
						return true;
					}
					count = 0;
				}

			}
		}
		return false;
	}

	bool SpriteBatch::isCollidingPhysicSpriteExceptUserDataStr2(long long id, std::vector<std::string> dataToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id : _collisionIds[id])
				{
					for (std::string data : dataToExcept)
					{
						if (getPhysicSpriteUserDataStr2(id) != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(dataToExcept.size()))
					{
						return true;
					}
					count = 0;
				}

			}
		}
		return false;
	}

	long long  SpriteBatch::isCollidingPhysicSpriteExceptIdsCount(long long id, std::vector<long long> idsToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id : _collisionIds[id])
				{
					for (long long data : idsToExcept)
					{
						if (id != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(idsToExcept.size()))
					{
						return count - static_cast<int>(idsToExcept.size());
					}
					count = 0;
				}

			}
		}
		return 0;
	}

	long long  SpriteBatch::isCollidingPhysicSpriteExceptUserDataNumCount(long long id, std::vector<long double> dataToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id : _collisionIds[id])
				{
					for (long double data : dataToExcept)
					{
						if (getPhysicSpriteUserDataNum(id) != data)
						{
							count++;
						}
					}
					if (count > static_cast<int>(dataToExcept.size()))
					{
						return count - static_cast<int>(dataToExcept.size())+1;
					}
					count = 0;
				}

			}
		}
		return 0;
	}

	long long  SpriteBatch::isCollidingPhysicSpriteExceptUserDataStrCount(long long id, std::vector<std::string> dataToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id2 : _collisionIds[id])
				{
					for (std::string data : dataToExcept)
					{
						if (getPhysicSpriteUserDataStr(id2) != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(dataToExcept.size()))
					{
						return count - static_cast<int>(dataToExcept.size())+1;
					}
					count = 0;
				}

			}
		}
		return false;
	}

	long long  SpriteBatch::isCollidingPhysicSpriteExceptUserDataStr2Count(long long id, std::vector<std::string> dataToExcept)
	{
		int count = 0;
		if (_bodyBatch.count(id) > 0)
		{
			if (_collisionIds.count(id) > 0)
			{
				for (long long id2 : _collisionIds[id])
				{
					for (std::string data : dataToExcept)
					{
						if (getPhysicSpriteUserDataStr2(id2) != data)
						{
							count++;
						}
					}
					if (count >= static_cast<int>(dataToExcept.size()))
					{
						return count - static_cast<int>(dataToExcept.size())+1;
					}
					count = 0;
				}

			}
		}
		return false;
	}

	b2Vec2 SpriteBatch::getPhysicSpriteVelocity(long long id)
	{
		if (_bodyBatch.count(id) > 0)
		{
			b2Vec2 tmp = _bodyBatch[id]->GetLinearVelocity();
			tmp.x *= 30.0f;
			tmp.y *= 30.0f;
			return tmp;
		}
	}

	float SpriteBatch::getPhysicSpriteAngVelocity(long long id)
	{
		if (_bodyBatch.count(id) > 0)
		{
			return static_cast<float>(_bodyBatch[id]->GetAngularVelocity() * 3.141592653589793 / 180);
		}
	}


}