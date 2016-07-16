#include "Wild_Encounter.h"

#include <iostream>

#include "asciimon_loader.h"
#include "game_funcs.h"
#include "console_funcs.h"
#include "animated_text.h"

namespace State
{


Wild_Encounter :: Wild_Encounter( Game_Main& game, unsigned enemyId, unsigned levelOfEnemy )
:   Encounter_Base ( game )
{
    loadEnemy( enemyId, levelOfEnemy );
    m_p_playerAsciimon = &getPlayer().getFrontAsciimon();

    initEncounter();
}


void Wild_Encounter :: loadEnemy( unsigned enemyId, unsigned levelOfEnemy )
{
    Asciimon_Loader loader;

    loader.load( &m_asciimon, enemyId );
    m_asciimon.setLevel( levelOfEnemy );
    m_p_enemyAsciimon = &m_asciimon;
}

void Wild_Encounter :: initEncounter()
{
    Console::clear();
    Animated_Text::quickText( "A wild " + m_asciimon.getName() + " has appeared!",
                              m_asciimon.getFrontImage() );
}















}
