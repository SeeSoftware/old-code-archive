#include "VectorFunctions.h"

namespace GESFML
{

	const void VectorFunctions::vectorNormalize(sf::Vector2f &vec)
	{
		sf::Vector2f vector;
		float length = vectorGetLength(vec);

		if (length != 0)
		{
			vector.x = vec.x / length;
			vector.y = vec.y / length;
		}

		vec = vector;
	}

	const float VectorFunctions::vectorGetLength(sf::Vector2f vec)
	{
		return sqrt(vec.x*vec.x + vec.y * vec.y);
	}

	const float VectorFunctions::vectorDistnace(sf::Vector2f from, sf::Vector2f to)
	{
		float distance = sqrt(pow(to.x - from.x, 2) + pow(to.y - from.y, 2));
		return distance;
	}

	const sf::Vector2f VectorFunctions::vectorNormalizeReturn(sf::Vector2f vec)
	{
		sf::Vector2f vector;
		float length = vectorGetLength(vec);

		if (length != 0)
		{
			vector.x = vec.x / length;
			vector.y = vec.y / length;
		}

		return vector;
	}

}