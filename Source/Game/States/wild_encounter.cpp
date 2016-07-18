#include "Wild_Encounter.h"

#include <iostream>

#include "asciimon_loader.h"
#include "game_funcs.h"
#include "console_funcs.h"
#include "animated_text.h"
#include "random_functions.h"
#include "sound_manager.h"
#include "Music_Manager.h"

namespace State
{


Wild_Encounter :: Wild_Encounter( Game_Main& game, unsigned enemyId, unsigned levelOfEnemy )
    :   Encounter_Base ( game )
{
    Music_Manager::pushSong( "Wild", 40 );
    loadEnemy( enemyId, levelOfEnemy );
    m_p_playerAsciimon = &getPlayer().getFrontAsciimon();

    Game::printToLog( "Wild Encounter Begun" );

    initEncounter();
}


void Wild_Encounter :: loadEnemy( unsigned enemyId, unsigned levelOfEnemy )
{
    Asciimon_Loader loader;

    loader.load( &m_asciimon, enemyId );
    m_p_enemyAsciimon = &m_asciimon;

    getEnemyAsciimon().setLevel( levelOfEnemy );
}

void Wild_Encounter :: initEncounter()
{
    Console::clear();
    std::string line ( 50, '0' );
    for ( int i = 0 ; i < 50 ; i++ )
    {
        std::cout << line << std::endl;
        Game::shortPause( 0.05 );
    }


    Animated_Text::quickTextCol( "A wild " + getEnemyAsciimon().getName() + " has appeared!",
                                 getEnemyAsciimon().getFrontImage(),
                                 0.05,
                                 Console::Foreground_Colour ( getEnemyAsciimon().getTypeColour() ) );
}

void Wild_Encounter :: enemyTurn ()
{
    Game::printToLog( "Enemy Turn of the Wild Encounter" );

    int enemyMove = Random::integer( 0, getEnemyAsciimon().getMoves().size() - 1 );

    attack ( getEnemyAsciimon(), getPlayerAsciimon(), getEnemyAsciimon().getMove( enemyMove ), false );
}


void Wild_Encounter :: enemyFainted  ()
{
    endBattle();
}


void Wild_Encounter :: tryRun()
{
    Console::clear();
    Game::message( "You successfully run away from " + m_asciimon.getName() );
    endBattle();
}

void Wild_Encounter :: tryCatch ()
{
    Animated_Text::quickTextCol( "You attempt to catch " + getEnemyAsciimon().getName() + "!",
                                 getEnemyAsciimon().getFrontImage(),
                                 0.05,
                                 Console::Foreground_Colour ( getEnemyAsciimon().getTypeColour() ) );
    Image ball( "Asciiball" );

    for ( int i = 0 ; i < 10 ; i++ )
    {
        Console::clear();
        Console::Foreground_Colour c = static_cast<Console::Foreground_Colour>
                                    ( Random::integer( 0, 10 ) );
        Console::setTextColour( c );
        ball.draw();
        Game::shortPause( 0.1 );
    }
    Console::resetColours();

    Game::message( "You successfully caught the " + m_asciimon.getName() + "!" );
    getPlayer().give( m_asciimon );
    endBattle();
}







}
