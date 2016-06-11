#include "keyboard.h"

#include <conio.h>

#include <iostream>



namespace Keyboard
{
    char
    getKey ()
    {
        char input = ' ';
        if ( kbhit() )
        {
            input =  getch();
        }
        return input;
    }

    char
    waitForKey ()
    {
        char input = ' ';
        while ( !kbhit() );
        input = getch();
        return input;
    }

    void
    waitForNoKey ()
    {
        while ( kbhit() );
    }
}
