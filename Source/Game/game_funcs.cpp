#include "game_funcs.h"

#include "windows_funcs.h"
#include "console_funcs.h"

#include <iostream>

namespace Game
{

void
shortPause ( double seconds )
{

    #ifdef __WIN32
        seconds *= 1000;
        Sleep(seconds);
    #endif // __WIN32
}

void
pressEnterToContinue ()
{
    Console::newLine();

    std::cout << "Press enter to continue...";
    std::cin.sync();
    std::cin.get();

    Console::newLine();
}

}
