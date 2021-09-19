#include "ContactListener.h"
#include "SpriteBatch.h"
#include <unordered_map>
namespace GESFML
{

	ContactListener::ContactListener()
	{
	}



	void ContactListener::BeginContact(b2Contact* contact)
	{
		b2Body* bodyA = contact->GetFixtureA()->GetBody();
		b2Body* bodyB = contact->GetFixtureB()->GetBody();

		if (bodyA == nullptr)return;
		if (bodyB == nullptr)return;

		std::cout << bodyA->GetFixtureList()->IsSensor() << bodyB->GetFixtureList()->IsSensor();

		if (bodyA->GetFixtureList()->IsSensor() && bodyB->GetFixtureList()->IsSensor()) return;
		if (bodyA->GetUserData() != bodyB->GetUserData())return;
		if (bodyA->GetUserData() == nullptr)return;
		if (bodyB->GetUserData() == nullptr)return;

		SpriteBatch * _batch = static_cast<SpriteBatch*>(bodyA->GetUserData());

		//getThe id by some checks
		long long idA;
		long long idB;

		for (auto x : _batch->getBodyBatch())
		{

			if (x.second->GetPosition().x == bodyA->GetPosition().x)
			{
				if (x.second->GetPosition().y == bodyA->GetPosition().y)
				{
					if (x.second->GetAngle() == bodyA->GetAngle())
					{
						if (x.second->GetType() == bodyA->GetType())
						{
							idA = x.first;

						}

					}
				}
			}

		}

		for (auto x : _batch->getBodyBatch())
		{

			if (x.second->GetPosition().x == bodyB->GetPosition().x)
			{
				if (x.second->GetPosition().y == bodyB->GetPosition().y)
				{
					if (x.second->GetAngle() == bodyB->GetAngle())
					{
						if (x.second->GetType() == bodyB->GetType())
						{
							idB = x.first;

						}

					}
				}
			}
		}

		if (idA == idB)
		{
			return;
		}

		if (_batch->getPhysicSpriteCollisionIdsBatch().count(idA) > 0)
		{

			_batch->getPhysicSpriteCollisionIdsBatch()[idA].push_back(idB);
			_batch->getPhysicSpriteCollisionIdsBatch()[idB].push_back(idA);
			//	if (idB == 13|| idA == 13)
			//	{
			//		std::cout << idA << " " << idB << "\n---------------------------\n";
			//	}

		}
	}
		void ContactListener::EndContact(b2Contact* contact)
		{
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();

			if (bodyA == nullptr)return;
			if (bodyB == nullptr)return;
			if (bodyA->GetFixtureList()->IsSensor() && bodyB->GetFixtureList()->IsSensor())return;
			if (bodyA->GetUserData() != bodyB->GetUserData())return;
			if (bodyA->GetUserData() == nullptr)return;
			if (bodyB->GetUserData() == nullptr)return;

			SpriteBatch * _batch = static_cast<SpriteBatch*>(bodyA->GetUserData());

			//getThe id by some checks
			long long idA;
			long long idB;


			for (auto x : _batch->getBodyBatch())
			{

				if (x.second->GetPosition().x == bodyA->GetPosition().x)
				{
					if (x.second->GetPosition().y == bodyA->GetPosition().y)
					{
						if (x.second->GetAngle() == bodyA->GetAngle())
						{
							if (x.second->GetType() == bodyA->GetType())
							{
								idA = x.first;

							}

						}
					}
				}

			}

			for (auto x : _batch->getBodyBatch())
			{

				if (x.second->GetPosition().x == bodyB->GetPosition().x)
				{
					if (x.second->GetPosition().y == bodyB->GetPosition().y)
					{
						if (x.second->GetAngle() == bodyB->GetAngle())
						{
							if (x.second->GetType() == bodyB->GetType())
							{
								idB = x.first;

							}

						}
					}
				}
			}

			if (idA == idB)
			{
				return;
			}

			if (_batch->getPhysicSpriteCollisionIdsBatch().count(idA) > 0)
			{
				for (int i = 0; i < _batch->getPhysicSpriteCollisionIdsBatch()[idA].size(); i++)
				{

					if (_batch->getPhysicSpriteCollisionIdsBatch()[idA][i] == idB)
					{

						_batch->getPhysicSpriteCollisionIdsBatch()[idA].erase(_batch->getPhysicSpriteCollisionIdsBatch()[idA].begin() + i);
						break;
					}
				}
			}

			if (_batch->getPhysicSpriteCollisionIdsBatch().count(idB) > 0)
			{
				for (int i = 0; i < _batch->getPhysicSpriteCollisionIdsBatch()[idB].size(); i++)
				{

					if (_batch->getPhysicSpriteCollisionIdsBatch()[idB][i] == idA)
					{

						_batch->getPhysicSpriteCollisionIdsBatch()[idB].erase(_batch->getPhysicSpriteCollisionIdsBatch()[idB].begin() + i);
						break;
					}
				}
			}


		}

	}
