#include "percentage_bar.h"

#include <iostream>

Percentage_Bar :: Percentage_Bar ()
:   m_line    ( BARS * 3, '-' )
{ }

void Percentage_Bar :: draw ( int curr, int max, Console::Foreground_Colour fullColour, Console::Foreground_Colour emptyColour )
{
    drawLine ();
    double full = (double)curr / ((double)max / (double)BARS);
    Console::setTextColour( fullColour );
    drawFullBars ( full );

    Console::setTextColour( emptyColour );
    int remainder = BARS - full;
    drawEmptyBars(remainder);

    Console::resetColours();
}

void Percentage_Bar :: drawFullBars ( int fullBars )
{
    for ( int i = 0 ; i < fullBars ; i++ ) {
        std::cout << "[O]";
    }
}

void Percentage_Bar :: drawEmptyBars ( int emptyBars )
{
    for ( int i = 0 ; i < emptyBars ; i++ ) {
        std::cout << "[X]";
    }
    Console::newLine();
    drawLine ();
}

void Percentage_Bar :: drawLine ()
{
    Console::setTextColour ( Console::Foreground_Colour::WHITE );

    std::cout << m_line << std::endl;
}
