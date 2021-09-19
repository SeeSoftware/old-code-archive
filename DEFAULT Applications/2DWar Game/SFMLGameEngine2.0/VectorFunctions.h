#pragma once
#include <SFML\Graphics.hpp>

namespace GESFML
{

class VectorFunctions
{
public:

	const static void vectorNormalize(sf::Vector2f &vec);
	const static sf::Vector2f vectorNormalizeReturn(sf::Vector2f vec);
	const static float vectorGetLength(sf::Vector2f vec);
	const static float vectorDistnace(sf::Vector2f from, sf::Vector2f to);



};

}


