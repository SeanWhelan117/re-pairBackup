/// @Author Michael Rainsford Ryan

#include "../include/Game.h"
#include <iostream>

Game::Game() :
	m_window{ sf::VideoMode::getDesktopMode(), "Basic Game", sf::Style::Fullscreen },
	//m_window{ sf::VideoMode{ 800u, 600u, 32u }, "Basic Game" },
	m_cameraController{ m_window },
	m_exitGame{ false },
	m_player{ m_spriteSheetTexture },
	m_blindMode{ false }
{
	sf::View view = m_window.getDefaultView();

	float heightPerWidth = view.getSize().y / view.getSize().x;

	view.setSize(800.0f, 800.0f * heightPerWidth);

	view.setSize(view.getSize());

	m_window.setView(view);
	m_window.setVerticalSyncEnabled(true);

	if (!m_spriteSheetTexture.loadFromFile("images//SpriteSheet.png"))
	{
		std::cout << "Error loading sprite sheet texture file" << std::endl;
	}

	if (!m_overlayTexture.loadFromFile("images//overlay.png"))
	{
		std::cout << "Error loading overlay texture file" << std::endl;
	}

	m_overlaySprite.setTexture(m_overlayTexture);
	m_overlaySprite.setOrigin(m_overlaySprite.getGlobalBounds().width / 2.0f, m_overlaySprite.getGlobalBounds().height / 2.0f);

	if (!m_backgroundTexture.loadFromFile("images//Background.png"))
	{
		std::cout << "Error loading texture file" << std::endl;
	}

	m_backgroundSprite.setTexture(m_backgroundTexture);
	m_backgroundSprite.setPosition(-150.0f, -150.0f);


	if (!m_backgroundMusic.openFromFile("sounds//backgroundMusic.ogg"))
	{
		std::cout << "Error opening music file" << std::endl;
	}

	m_backgroundMusic.setLoop(true);

	if (!m_bleepBuffer.loadFromFile("sounds//sonarBleep.wav"))
	{
		throw("Error loading bleep sound file");
	}

	m_bleepSound.setBuffer(m_bleepBuffer);

	if (!m_winBuffer.loadFromFile("sounds//win.wav"))
	{
		throw("Error loading win sound file");
	}

	m_winSound.setBuffer(m_winBuffer);

	if (!m_loseBuffer.loadFromFile("sounds//lose.wav"))
	{
		throw("Error loading lose sound file");
	}

	m_loseSound.setBuffer(m_loseBuffer);

	startRound();
	m_gamestate = GameState::Licence;
}

Game::~Game()
{

}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float FPS = 60.0f;
	sf::Time timePerFrame = sf::seconds(1.0f / FPS); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // Run as many times as possible
		timeSinceLastUpdate += clock.restart();
		if (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // Run at a minimum of 60 fps
			update(timePerFrame); // 60 fps
		}
		render(); // Run as many times as possible
	}
}

void Game::processEvents()
{
	sf::Event nextEvent;
	while (m_window.pollEvent(nextEvent))
	{
		if (sf::Event::Closed == nextEvent.type) // check if the close window button is clicked on.
		{
			m_window.close();
		}
		if (sf::Event::KeyPressed == nextEvent.type)
		{
			if (m_gamestate == GameState::End)
			{
				if (sf::Keyboard::Space == nextEvent.key.code)
				{
					startRound();
				}
				if (sf::Keyboard::B == nextEvent.key.code)
				{
					m_blindMode = !m_blindMode;
				}
			}
			if (sf::Keyboard::Escape == nextEvent.key.code)
			{
				m_window.close();
			}

			if (m_gamestate == GameState::Splash)
			{
				if (sf::Keyboard::B == nextEvent.key.code)
				{
					m_blindMode = !m_blindMode;
				}
			}
		}

		m_gui.processEvents(nextEvent, m_backgroundMusic, m_gameTimer, m_gamestate, m_window);
	}
}

void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}

	if (m_gamestate == GameState::Splash
		|| m_gamestate == GameState::Gameplay)
	{
		for (NPC& npc : m_npcs)
		{
			npc.update();
		}
	}

	if (m_gamestate == GameState::Gameplay)
	{
		if (m_player.winCheck())
		{
			m_gamestate = GameState::End;
			m_winSound.play();
		}

		m_player.update();
		timeBar();
		m_timeBar.setPosition(sf::Vector2f(m_player.getPosition().x, m_player.getPosition().y + m_player.getSize().y*1.2));

		m_cameraController.moveWindow(m_player.getPosition());

		 elapsedSeconds = m_gameTimer.getElapsedTime().asSeconds();

		/*m_text.setString(std::to_string(20 - static_cast<int>(elapsedSeconds)));
		m_text.setPosition(m_player.getPosition().x + m_player.getSize().x / 2.0f, m_player.getPosition().y + m_player.getSize().y);
		m_text.setOrigin(m_text.getGlobalBounds().width / 2.0f, 0.0f);*/

		if (elapsedSeconds >= 20.0f)
		{
			m_gamestate = GameState::End;
			m_loseSound.play();
		}

		if (m_bleepTimer.getElapsedTime().asMilliseconds() > m_player.getDistanceToTarget()  * 5.0f)
		{
			if (m_blindMode)
			{
				m_bleepSound.play();
			}

			m_bleepTimer.restart();
		}
	}

	m_gui.update(m_gamestate);
}

void Game::render()
{
	m_window.clear(sf::Color::White);

	if (m_gamestate == GameState::Splash
		|| m_gamestate == GameState::Gameplay)
	{
		m_window.draw(m_backgroundSprite);

		if (!m_blindMode)
		{
			for (NPC& npc : m_npcs)
			{
				m_window.draw(npc);
			}
		}

		m_window.draw(m_player);

		m_window.draw(m_timeBar);


		m_window.draw(m_timeBar);

		m_overlaySprite.setPosition(m_window.getView().getCenter());
		m_window.draw(m_overlaySprite);
	}

	
	m_gui.draw(m_window, m_gamestate);
	
	
	m_window.display();
}

void Game::startRound()
{
	m_cameraController.reset();

	m_player.setup();

	m_npcs.clear();

	for (int i = 0; i < NPC_NUM; i++)
	{
		m_npcs.push_back(NPC(m_spriteSheetTexture));
	}

	int index = rand() % NPC_NUM;
	m_player.setTarget(&m_npcs.at(index));
	m_npcs.at(index).setPerson(&m_player);

	m_backgroundMusic.stop();
	m_backgroundMusic.play();

	m_gamestate = GameState::Gameplay;

	m_gameTimer.restart();
}

void Game::timeBar()
{
	float xPos = (20 - elapsedSeconds) * (80 / 20);
	m_timeBar.setOrigin(sf::Vector2f(xPos / 2, 5));

	if (elapsedSeconds >= 15)
	{
		m_timeBar.setFillColor(sf::Color::Red);
	}
	if (elapsedSeconds > 5 && elapsedSeconds <=14)
	{
		m_timeBar.setFillColor(sf::Color::Yellow);
	}
	if (elapsedSeconds <5 && elapsedSeconds >= 0)
	{
		m_timeBar.setFillColor(sf::Color::Green);
	}


	m_timeBar.setPosition(sf::Vector2f(m_player.getPosition().x, m_player.getPosition().y + m_player.getSize().y * 1.2));

	m_timeBar.setSize(sf::Vector2f(xPos, 10));
}
