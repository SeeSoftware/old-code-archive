#pragma once
#include <SFML\Graphics.hpp>

namespace GESFML
{

class VectorFunctions
{
public:

	const void vectorNormalize(sf::Vector2f &vec);
	const sf::Vector2f vectorNormalizeReturn(sf::Vector2f vec);
	const float vectorGetLength(sf::Vector2f vec);
	const float vectorDistnace(sf::Vector2f from, sf::Vector2f to);



};

}


