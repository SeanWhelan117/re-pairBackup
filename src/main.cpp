/// re-pair
/// @Author Michael Rainsford Ryan
/// @Date 01/02/2020

#ifdef SFML_STATIC
#pragma comment(lib,"sfml-graphics-s.lib")
#pragma comment(lib,"freetype.lib")
#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"sfml-system-s.lib")
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"sfml-window-s.lib")
#pragma comment(lib,"gdi32")
#pragma comment(lib,"winmm")
#pragma comment(lib,"sfml-audio-s.lib")
#pragma comment(lib,"flac.lib")
#pragma comment(lib,"ogg.lib")
#pragma comment(lib,"vorbisenc.lib")
#pragma comment(lib,"vorbisfile.lib")
#pragma comment(lib,"vorbis.lib")
#pragma comment(lib,"openal32.lib")
#pragma comment(lib,"sfml-main.lib")
#pragma comment(lib,"sfml-network-s.lib")
#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"openal32.lib")
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#else
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#endif

#include "../include/Game.h"

int main()
{
	srand(static_cast<unsigned>(time(nullptr)));

	Game game;
	game.run();

	return 0;
}
