#include "../include/MathUtility.h"

///////////////////////////////////////////////////////////////////////////////
const float MathUtility::length(sf::Vector2f const t_vector)
{
	return sqrtf(t_vector.x * t_vector.x + t_vector.y * t_vector.y);
}

///////////////////////////////////////////////////////////////////////////////
const sf::Vector2f MathUtility::normalise(sf::Vector2f const t_vector)
{
	const float len = length(t_vector);

	if (len == 0.0f)
	{
		throw("Error: normalise function requires a non zero vector");
	}

	return t_vector / len;
}

///////////////////////////////////////////////////////////////////////////////
sf::Color MathUtility::randomColor()
{
	return sf::Color{ static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255),static_cast<sf::Uint8>(rand() % 255) };
}

///////////////////////////////////////////////////////////////////////////////