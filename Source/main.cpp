#include <iostream>
#ifdef __WIN32
    #define _WIN32_WINNT 0x0500 //For getting console window
#endif // __WIN32

#include "Utilities/windows_funcs.h"
#include "Game/game.h"
#include "game_funcs.h"

#include <ctime>
#include <stdexcept>

#include <SFML/Audio.hpp>

#include "animated_text.h"

void
setupConsole();

void test()
{
    Game::pressEnterToContinue();
}

int main()
{
    srand(time(NULL));

    Image image( "logo" );
    image.draw();

    test();

    sf::Music music;
    if ( ! music.openFromFile( "Data/Music/Theme.ogg") ) throw std::runtime_error ( "Song not loaded" );
    music.setVolume ( 10 );
    music.play();

    setupConsole();

    Game_Main game;
    game.runLoop();

    return EXIT_SUCCESS;
}

void setupConsole()
{
    #ifdef __WIN32
        constexpr short consoleWidth = 500;
        constexpr short consoleHeight = 700;

        HWND console = GetConsoleWindow();
        MoveWindow(console, 0, 0, consoleWidth, consoleHeight, TRUE);
        //MoveWindow(console, -1750, 0, consoleWidth, consoleHeight, TRUE);
    #endif // __WIN32
}
