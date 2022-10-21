#ifndef PERSON_H
#define PERSON_H

/// @Author Michael R Ryan
/// @Date 01/02/2020

#include <SFML/Graphics.hpp>
#include <iostream>
#include "Config.h"

class Person : public sf::Drawable
{
public:
	Person(sf::Texture const & t_spriteSheetTexture, int t_animIntervalMS);
	Person(sf::Texture const& t_spriteSheetTexture, int t_animIntervalMS, float const t_x, float const t_y);

	void setupSprites(sf::Texture const& t_spriteSheetTexture);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	const sf::Vector2f getPosition() const;
	void setPosition(float t_x, float t_y);
	const sf::Vector2f getSize() const;

	void setFillColor(sf::Color t_hairColor, sf::Color t_shirtColor, sf::Color t_trousersColor);
	sf::Color getFillColor();

	sf::Color getHairColor();
	sf::Color getShirtColor();
	sf::Color getTrousersColor();

	const int getFrameIndex() const;
	void setFrameIndex(int const t_index);

	void setAnimationInterval(int t_milliseconds);


protected:
	void move(float t_x, float t_y);
	void move(sf::Vector2f t_vector);

	void animateMovement(sf::Vector2f t_movementVector);
	void setScale(float t_scaleX, float t_scaleY);

private:
	sf::RectangleShape m_boundingBox;

	sf::Sprite m_fullSprite;
	sf::Sprite m_hairSprite;
	sf::Sprite m_shirtSprite;
	sf::Sprite m_trousersSprite;

	int m_frameIndex;
	static constexpr float m_SCALE{ 3.7f };

	sf::Clock m_animationTimer;
	int m_animIntervalMS;
};

#endif // !PERSON_H