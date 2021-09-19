#include "Color.h"

namespace GESFML
{

	Color::Color()
	{
		r = 0;
		g = 0;
		b = 0;
		a = 255;
	}


	Color::~Color()
	{
	}

	Color::Color(int R, int G, int B)
	{
		r = R;
		g = G;
		b = B;
		a = 255;
	}

	Color::Color(int R, int G, int B, int A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}

	Color::Color(sf::Color color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

	sf::Color Color::getSfColor()
	{
		return sf::Color(r, g, b, a);
	}

	void Color::setSfColor(sf::Color color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}

}