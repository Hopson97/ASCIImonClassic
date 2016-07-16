#include "new_game.h"

#include <iostream>
#include <string>

#include "Image.h"
#include "animated_text.h"
#include "talk_scene.h"

#include "roaming.h"




namespace State
{

New_Game::New_Game(Game_Main& game)
:   State_Base ( game )
{

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

    getGame().getStates().pushState( new State::Roaming( getGame(), {0, 0 } ) );
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

}
