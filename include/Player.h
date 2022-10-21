#ifndef PLAYER_H
#define PLAYER_H

/// @Author Michael R Ryan
/// @Author Sean Whelan
/// @Date 01/02/2020

#include "Person.h"
#include "Config.h"
#include "MathUtility.h"

class Player : public Person
{
public:
	Player(sf::Texture const& t_spriteSheetTexture);

	void setup();

	void update();

	bool winCheck();

	void setTarget(Person * t_targetPtr);

	const float getDistanceToTarget() const;

private:
	float m_speed;
	Person * m_targetPtr;
};

#endif // !PLAYER_H