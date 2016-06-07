#include "game_funcs.h"

#include "windows_funcs.h"
#include "console_funcs.h"
#include "clock.h"

#include <iostream>

namespace Game
{

void
shortPause ( double seconds )
{
    Clock clock;
    while ( clock.getCurrentTime() < seconds );
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
