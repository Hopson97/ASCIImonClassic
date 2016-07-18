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
#include "Music_Manager.h"
#include "game_funcs.h"

void
setupConsole();

void test()
{
    Game::pressEnterToContinue();
}

int main()
{
    srand(time(NULL));
    setupConsole();
    Game::openLog();

    Image image( "logo" );
    image.draw();

    test();

    Game_Main game;
    game.runLoop();

    return EXIT_SUCCESS;
}

void setupConsole()
{
    #ifdef __WIN32
        constexpr int consoleWidth = 800;
        constexpr int consoleHeight = 1280;

        HWND console = GetConsoleWindow();
        MoveWindow(console, 0, 0, consoleWidth, consoleHeight, TRUE);
        MoveWindow(console, -1450, 50, consoleWidth, consoleHeight, TRUE);
    #endif // __WIN32
}
