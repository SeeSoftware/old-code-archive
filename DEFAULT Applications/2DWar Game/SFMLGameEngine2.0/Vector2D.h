#pragma once
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
namespace GESFML
{

	class Vector2D
	{
	public:
		Vector2D();
		~Vector2D();

		Vector2D(float X, float Y);
		Vector2D(b2Vec2 vec);
		Vector2D(sf::Vector2f vec);

		b2Vec2 getB2Vec();
		sf::Vector2f getSfVec();
		void setB2Vec(b2Vec2 vec);
		void setSfVec(sf::Vector2f vec);
		void floorPos();

		float x=0;
		float y=0;
	};

}
