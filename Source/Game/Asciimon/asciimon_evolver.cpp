#include "asciimon_evolver.h"

#include "asciimon_loader.h"
#include "animated_text.h"

#include "game_funcs.h"

#include "console_funcs.h"

Asciimon_Evolver :: Asciimon_Evolver( Asciimon& asciimon, unsigned id )
:   m_asciimon      ( asciimon )
,   m_evolveIntoId  ( id )
{}

void Asciimon_Evolver :: evolve ()
{
    Asciimon newAsciimon = getEvolvingInto ();

    Animated_Text::quickText( "Your " + m_asciimon.getName() + " is evolving!" );

    std::string oldName = m_asciimon.getName();

    for ( double i = 7 ; i > 0 ; i-- )
    {
        m_asciimon.drawFront();
        Game::shortPause( i / 10 );
        Console::clear();

        newAsciimon.drawFront();
        Game::shortPause( i / 10 );
        Console::clear();
    }
    //sound
    m_asciimon = newAsciimon;
    Animated_Text::quickTextCol ( "Congratulations! Your " + oldName + " has evolved into a " + newAsciimon.getName() + "!",
                               newAsciimon.getFrontImage(),
                               0.05,
                               m_asciimon.getTypeColour() );
}

//Make sure the Asciimon being evolved into is loaded into the cache and then returns it back
Asciimon Asciimon_Evolver :: getEvolvingInto ()
{
    Asciimon evolvingInto;
    Asciimon_Loader loader;

    loader.load( &evolvingInto, m_evolveIntoId );
    evolvingInto.setLevel( m_asciimon.getLevel().getLevel() );

    return evolvingInto;
}
