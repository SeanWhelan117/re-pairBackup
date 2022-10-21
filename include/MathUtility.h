#ifndef MATH_UTILITY_H
#define MATH_UTILITY_H

/// @Author Michael R Ryan
/// @Date 01/02/2020

#include <SFML/Graphics.hpp>

class MathUtility
{
public:

	static const float length(sf::Vector2f const t_vector);

	static const sf::Vector2f normalise(sf::Vector2f const t_vector);

	static sf::Color randomColor();
};

#endif // !MATH_UTILITY_H