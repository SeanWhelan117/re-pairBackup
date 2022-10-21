#include "../include/GUI.h"

GUI::GUI()
{
	if (!m_buttonsTexture.loadFromFile("images//buttons.png"))
	{
		throw("Error loading button sprites");
	}
	if (!m_licenceTexture.loadFromFile("images//licence.png"))
	{
		throw("Error loading licence sprites");
	}
	if (!m_restartButtonTexture.loadFromFile("images//restartButton.png"))
	{
		throw("Error loading licence sprites");
	}

	m_playButtonSprite.setTexture(m_buttonsTexture);
	m_exitButtonSprite.setTexture(m_buttonsTexture);
	m_licenceSprite.setTexture(m_licenceTexture);
	m_restartButton.setTexture(m_restartButtonTexture);

	m_restartButton.setOrigin(16, 16);
	m_restartButton.scale(3.0f, 3.0f);
	m_restartButton.setPosition(400.0f, 230.0f);
	

	m_licenceSprite.setOrigin(m_licenceSprite.getGlobalBounds().width / 2.0f, m_licenceSprite.getGlobalBounds().height / 2.0f);
	m_licenceSprite.setScale(1.5f, 1.5f);
	m_licenceSprite.setPosition(400.0f, 250.0f);

	m_playButtonSprite.setTextureRect({ 0,0,77,77 });
	m_exitButtonSprite.setTextureRect({ 77,0,77,77 });

	m_playButtonSprite.setOrigin(m_playButtonSprite.getGlobalBounds().width / 2.0f, m_playButtonSprite.getGlobalBounds().height / 2.0f);
	m_exitButtonSprite.setOrigin(m_exitButtonSprite.getGlobalBounds().width / 2.0f, m_exitButtonSprite.getGlobalBounds().height / 2.0f);

	m_playButtonSprite.setPosition(400.0f, 200.0f);
	m_exitButtonSprite.setPosition(400.0f, 300.0f);

	m_selectCircle.setRadius(50.0f);
	m_selectCircle.setFillColor(sf::Color::Transparent);
	m_selectCircle.setOutlineColor(sf::Color{ 0,0,100,100 });
	m_selectCircle.setOutlineThickness(2.0f);
	m_selectCircle.setOrigin(m_selectCircle.getRadius(), m_selectCircle.getRadius());

	m_selectCircle.setPosition(m_playButtonSprite.getPosition());
}

void GUI::draw(sf::RenderWindow& t_window, GameState t_gameState)
{
	if (GameState::Splash == t_gameState)
	{
		t_window.draw(m_playButtonSprite);
		t_window.draw(m_exitButtonSprite);
		t_window.draw(m_selectCircle);
	}
	else if (GameState::Licence == t_gameState)
	{
		t_window.draw(m_licenceSprite);
	}
	else if (GameState::End == t_gameState)
	{
		m_restartButton.setPosition(t_window.getView().getCenter());
		t_window.draw(m_restartButton);
	}
}

void GUI::processEvents(sf::Event const& t_event, sf::Music& t_music, sf::Clock& t_clock, GameState& t_gamestate, sf::RenderWindow& t_window)
{
	if (t_gamestate == GameState::Splash)
	{
		if (sf::Event::KeyPressed == t_event.type)
		{
			if (sf::Keyboard::Down == t_event.key.code || sf::Keyboard::Up == t_event.key.code)
			{
				if (m_selectCircle.getPosition() == m_playButtonSprite.getPosition())
				{
					m_selectCircle.setPosition(m_exitButtonSprite.getPosition());
				}
				else
				{
					m_selectCircle.setPosition(m_playButtonSprite.getPosition());
				}
			}
			if (sf::Keyboard::Space == t_event.key.code)
			{
				if (m_selectCircle.getPosition() == m_playButtonSprite.getPosition())
				{
					t_music.stop();
					t_music.play();

					t_gamestate = GameState::Gameplay;

					t_clock.restart();
				}
				else
				{
					t_window.close();
				}
			}
		}
	}
}

void GUI::update(GameState & t_gamestate)
{
	if (t_gamestate == GameState::End)
	{
		m_restartButton.rotate(-0.1f);
	}

	if (t_gamestate == GameState::Licence)
	{
		if (m_licenceTimer.getElapsedTime().asSeconds() > 1.0f)
		{
			t_gamestate = GameState::Splash;
		}
	}
}
