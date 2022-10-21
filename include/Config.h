#ifndef CONFIG_H
#define CONFIG_H

/// @Author Michael R Ryan
/// @Date 01/02/2020

const float GAME_WIDTH{ 1200.0f };
const float GAME_HEIGHT{ 1200.0f };
const int NPC_NUM{ 100 };

enum class GameState
{
	Licence,
	Splash,
	Gameplay,
	End
};

#endif // !CONFIG_H

