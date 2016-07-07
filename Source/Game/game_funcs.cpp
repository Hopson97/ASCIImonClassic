#include "game_funcs.h"

#include "../Utilities/windows_funcs.h"
#include "../Utilities/console_funcs.h"
#include "../Utilities/clock.h"

#include <iostream>

namespace Game
{

void shortPause ( double seconds )
{
    Clock clock;
    while ( clock.getCurrentTime() < seconds );
}

void pressEnterToContinue ()
{
    Console::newLine();

    std::cout << "Press enter to continue...";
    std::cin.sync();
    std::cin.get();

    Console::newLine();
}

}
