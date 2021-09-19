#include "Vector2D.h"

namespace GESFML
{

	Vector2D::Vector2D()
	{
		x = 0;
		y = 0;

	}


	Vector2D::~Vector2D()
	{
	}


	Vector2D::Vector2D(float X, float Y)
	{
		x = X;
		y = Y;	
	}

	Vector2D::Vector2D(b2Vec2 vec)
	{
		x = vec.x;
		y = vec.y;
	}

	Vector2D::Vector2D(sf::Vector2f vec)
	{
		x = vec.x;
		y = vec.y;
	}

	b2Vec2 Vector2D::getB2Vec()
	{
		return b2Vec2(x, y);
	}

	sf::Vector2f Vector2D::getSfVec()
	{
		return sf::Vector2f(x, y);
	}

	void Vector2D::setB2Vec(b2Vec2 vec)
	{
		x = vec.x;
		y = vec.y;
	}

	void Vector2D::setSfVec(sf::Vector2f vec)
	{
		x = vec.x;
		y = vec.y;
	}

	void Vector2D::floorPos()
	{
		x = floor(x);
		y = floor(y);
	}

}