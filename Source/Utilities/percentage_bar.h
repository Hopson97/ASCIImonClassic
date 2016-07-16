#ifndef PERCENTAGE_BAR_H
#define PERCENTAGE_BAR_H

#include "console_funcs.h"

#include <string>

class Percentage_Bar
{
    public:
        Percentage_Bar();

        void draw   ( int curr, int max, Console::Foreground_Colour fullColour, Console::Foreground_Colour emptyColour );

    private:
        void drawLine ();

        void drawFullBars    ( int fullBars );

        void drawEmptyBars   ( int emptyBars );


        std::string m_line;

        constexpr static int BARS = 20;

};

#endif // PERCENTAGE_BAR_H
