#include "animated_text.h"

#include "clock.h"
#include "game_funcs.h"
#include "console_funcs.h"

#include <iostream>

Animated_Text :: Animated_Text ( const Image& image, double time )
:  m_time ( time )
,   m_image ( &image )
{ }

Animated_Text :: Animated_Text ( const std::string& text, double time )
:   m_text ( text )
,   m_time ( time )
{ }


Animated_Text :: Animated_Text ( const std::string& text, const Image& image, double time )
:   m_text  ( text )
,   m_time  ( time )
,   m_image ( &image )
{ }


void Animated_Text :: display ()
{
    Clock clock;

    for ( size_t i = 0 ; i < m_text.size() + 1 ; i++ )
    {
        clock.restart();
        Console::clear();

        if ( m_image )
            m_image->draw();

        Console::newLine();

        std::cout <<  m_text.substr( 0, i ) << std::endl;
        while ( clock.getCurrentTime() < m_time );
    }
    Game::pressEnterToContinue();
    Console::clear();
}


void Animated_Text :: setText ( const std::string& text )
{
    m_text = text;
}


void Animated_Text :: operator = ( const std::string& text )
{
     m_text = text;
}

void Animated_Text :: quickText ( const std::string& text, double time )
{
    Animated_Text animText ( text, time );
    animText.display();
}

void Animated_Text :: quickText ( const std::string& text, const Image& image, double time )
{
    Animated_Text animText ( text, image, time );
    animText.display();
}














