#ifndef CONSOLE_FUNCS_H
#define CONSOLE_FUNCS_H

#include "e_console_colours.h"

namespace Console
{
    void clear               ();

    void setTextColour       ( Foreground_Colour colour );

    void setBackgroundColour ( Background_Colour colour);

    void resetColours        ();

    void newLine             ();

    void lineStartSpace      ();

    void printTenBlankLines  ();

    void printInvalidInput   ();

}



#endif // CONSOLE_FUNCS_H
