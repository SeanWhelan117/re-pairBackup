#include "../include/NPC.h"

/// @Author Michael R Ryan
/// @Date 01/02/2020

NPC::NPC(sf::Texture const& t_spriteSheetTexture) :
	m_velocity{ 1.0f, 0.0f },
	Person(t_spriteSheetTexture, 500,
		static_cast<float>(rand() % static_cast<int>(GAME_WIDTH - Person::getPosition().x)),
		static_cast<float>(rand() % static_cast<int>(GAME_HEIGHT - Person::getSize().y)))
{
	if (rand() % 15 == 0)
	{
		setAnimationInterval(200);
		m_velocity.x = 5.0f;
	}
}

void NPC::update()
{
	sf::Vector3f vector3 = { m_velocity.x, m_velocity.y, 0.0f };

	vector3 = sf::Matrix3f::RotationZ(static_cast<float>(rand() % 20 - 10)) * vector3;

	m_velocity.x = vector3.x;
	m_velocity.y = vector3.y;

	move(m_velocity);

	if (Person::getPosition().x + Person::getSize().x > GAME_WIDTH)
	{
		m_velocity.x *= -1;
	}

	if (Person::getPosition().x < 0.0f)
	{
		m_velocity.x *= -1;
	}

	if (Person::getPosition().y + Person::getSize().y > GAME_HEIGHT)
	{
		m_velocity.y *= -1;
	}

	if (Person::getPosition().y < 0.0f)
	{
		m_velocity.y *= -1;
	}
}

void NPC::setPerson(Person* t_person)
{
	setFillColor(t_person->getHairColor(), t_person->getShirtColor(), t_person->getTrousersColor());
	setAnimationInterval(500);
	m_velocity = { 1.0f, 0.0f };
}
