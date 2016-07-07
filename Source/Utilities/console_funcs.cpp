#include "console_funcs.h"

#include <cstdlib>
#include <iostream>

#include "t_casts.h"

namespace Console
{

void clear ()
{
    #ifdef __WIN32
        char fill = ' ';
        COORD tl = {0,0};
        CONSOLE_SCREEN_BUFFER_INFO s;
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        GetConsoleScreenBufferInfo(console, &s);
        DWORD written, cells = s.dwSize.X * s.dwSize.Y;
        FillConsoleOutputCharacter(console, fill, cells, tl, &written);
        FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
        SetConsoleCursorPosition(console, tl);
    #else
        system( "cls" );
    #endif
}

void setTextColour ( Foreground_Colour colour )
{
    #ifdef __WIN32
        SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE),
                                  Convert::shortUnsigned( colour ) );
    #endif // __WIN32
}

void setBackgroundColour ( Background_Colour colour)
{
    #ifdef __WIN32
        SetConsoleTextAttribute ( GetStdHandle ( STD_OUTPUT_HANDLE),
                                  Convert::shortUnsigned( colour ) );
    #endif // __WIN32
}

void resetColours ()
{
    setBackgroundColour ( Background_Colour::BLACK);
    setTextColour       ( Foreground_Colour::WHITE );
}

void newLine ()
{
    std::cout << std::endl;
}

void lineStartSpace ()
{
    //Basically it looks a lot better if the map doesn't start in the top left
    std::cout << "         ";
}

void printTenBlankLines  ()
{
    for ( int i = 0 ; i < 10 ; i++ )
    {
        std::cout << std::endl;
    }
}


}
