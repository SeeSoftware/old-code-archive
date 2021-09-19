#pragma once
#include <SFML\Graphics.hpp>

namespace GESFML
{

	class Color
	{
	public:
		Color();
		Color(int R, int G, int B);
		Color(int R, int G, int B, int A);
		Color(sf::Color color);
		~Color();

		sf::Color getSfColor();
		void setSfColor(sf::Color color);

		int r=0;
		int g=0;
		int b=0;
		int a=0;
	};

}