#include "new_game.h"

#include <iostream>
#include <string>

#include "Image.h"
#include "animated_text.h"
#include "talk_scene.h"
#include "console_funcs.h"

#include "roaming.h"
#include "asciimon.h"
#include "asciimon_loader.h"
#include "general_funcs.h"

#include "Music_Manager.h"

namespace State
{

New_Game::New_Game(Game_Main& game)
:   State_Base ( game )
{
    Asciimon_Loader loader;

    loader.load( &grass, 1 );
    loader.load( &water, 4 );
    loader.load( &fire, 7 );

    m_asciimon.push_back( &grass );
    m_asciimon.push_back( &water );
    m_asciimon.push_back( &fire );

    for ( auto& a : m_asciimon )
    {
        a->setLevel ( 5 );
    }
    Music_Manager::pushSong( "Start", 50 );
}



void New_Game :: input()
{
    Image image( "prof" );

    Talk_Scene profIntro( "new_game_1", image );
    profIntro.begin();

    std::string name;
    getName( name );

    Talk_Scene profOutro( "new_game2", image );
    profOutro.setVar( "name", name );
    profOutro.begin();

    printAsciimnStarters();

    int option = General::getInput( 1, 3, std::bind( &printAsciimnStarters, this ),
                                          std::bind( &invalid,              this )
                                   );

    Talk_Scene asciimonGiven ( "new_game3", image );
    asciimonGiven.setVar( "am_name", m_asciimon.at( option - 1 )->getName() );
    asciimonGiven.begin();


    getPlayer().give( *m_asciimon.at( option - 1 ) );
    getGame().getStates().pushState( new State::Roaming( getGame(), {10003, 10003 } ) );
}



void New_Game :: getName( std::string& name )
{
    std::cout << "Please enter your name." << std::endl;
    std::getline( std::cin, name );
    if ( name.length() > 10 ) name = name.substr( 0,10 );

    getGame().getPlayer().setName( name );
}


void New_Game :: update()
{}

void New_Game :: draw()
{}

void New_Game :: printAsciimnStarters () const
{
    std::cout << "1. Would you like the grass type, " << grass.getName() << "?" << std::endl;
    grass.drawFront();
    Console::newLine();

    std::cout << "2. Would you like the water type, " << water.getName() << "?" << std::endl;
    water.drawFront();
    Console::newLine();

    std::cout << "3. Would you like the fire type, " << fire.getName() << "?" << std::endl;
    fire.drawFront();
    Console::newLine();
}

void New_Game :: invalid()
{
    Image image( "prof" );
    Animated_Text::quickText( "no, no no! Pick 1-3! ", image, 0.08 );
}

}
