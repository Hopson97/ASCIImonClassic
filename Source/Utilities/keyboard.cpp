#include "keyboard.h"

#include <conio.h>

#include <iostream>

#include "../Game/game_funcs.h"



namespace Keyboard
{
    char getKey ()
    {
        char input = ' ';
        if ( kbhit() )
        {
            input =  getch();
        }
        return input;
    }

    char waitForKey ()
    {
        char input = ' ';
        while ( !kbhit() );
        input = getch();

        return input;
    }

    void waitForNoKey ()
    {
        while ( kbhit() );
    }
}
