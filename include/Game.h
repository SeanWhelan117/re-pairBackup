/// @Author Michael Rainsford Ryan

#ifndef GAME
#define GAME

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "player.h"
#include "NPC.h"
#include "CameraController.h"
#include "GUI.h"

class Game
{
public:

	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(sf::Time t_deltaTime);
	void render();

	void startRound();
	void timeBar();

	sf::RenderWindow m_window;
	bool m_exitGame;

	Player m_player;

	std::vector<NPC> m_npcs;

	CameraController m_cameraController;

	sf::Texture m_backgroundTexture;
	sf::Sprite m_backgroundSprite;
	sf::RectangleShape m_timeBar;

	GameState m_gamestate;

	sf::Clock m_gameTimer;
	float elapsedSeconds = 0;


	sf::Texture m_spriteSheetTexture;

	sf::Texture m_overlayTexture;
	sf::Sprite m_overlaySprite;

	sf::Music m_backgroundMusic;

	sf::SoundBuffer m_bleepBuffer;
	sf::Sound m_bleepSound;

	sf::SoundBuffer m_winBuffer;
	sf::Sound m_winSound;

	sf::SoundBuffer m_loseBuffer;
	sf::Sound m_loseSound;

	sf::Clock m_bleepTimer;

	bool m_blindMode;

	GUI m_gui;
};

#endif // !GAME

