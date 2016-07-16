#include "b_encounter.h"

#include "percentage_bar.h"
#include "general_funcs.h"
#include "game_funcs.h"
#include "t_casts.h"

#include <iostream>

namespace State
{

Encounter_Base :: Encounter_Base ( Game_Main& game )
:   State_Base ( game )
{

}


void Encounter_Base :: input()
{
    int option = getBattleOption( 1, 4, std::bind( &Encounter_Base::printInitOptions, this ) );
    gotoBattleOption( option );
}

void Encounter_Base :: update()
{
    getGame().setRedrawNeeded();
}

void Encounter_Base :: draw()
{
    drawHealthBar   ( *m_p_enemyAsciimon );
    drawName        ( *m_p_enemyAsciimon );
    m_p_enemyAsciimon->getFrontImage().draw();

    for ( int i = 0 ; i < 8 ; i ++ ) Console::newLine();

    m_p_playerAsciimon->getBackImage().draw();
    drawName        ( *m_p_playerAsciimon );
    drawHealthBar   ( *m_p_playerAsciimon );
}

void Encounter_Base :: haveTurn()
{

}


void Encounter_Base :: drawHealthBar ( const Asciimon& asciimon ) const
{
    Percentage_Bar bar;

    bar.draw( asciimon.getStat ( Stat_Name::Hit_Points ).getCurrValue(),
              asciimon.getStat ( Stat_Name::Hit_Points ).getMaxValue(),
              Console::Foreground_Colour::GREEN,
              Console::Foreground_Colour::RED
            );
}

void Encounter_Base :: drawName ( const Asciimon& asciimon ) const
{
    std::cout << asciimon.getName() << std::endl;
}

void Encounter_Base :: invalidInput   ()
{
    Console::printInvalidInput();
    getGame().setRedrawNeeded();
    draw();
}

int Encounter_Base :: getBattleOption( int min, int max, std::function<void(void)> failSafe )
{
    int option = 0;
    std::string input;
    while ( true )
    {
        std::getline( std::cin, input );
        if ( !General::isStringNumrical( input ) )
        {
            invalidInput();

            continue;
        }

        option = Convert::toNumber<int>(input);

        if ( !General::numberBetween( 1, 4, option ) )
        {
            invalidInput();
            continue;
        }
    }
}

void Encounter_Base :: gotoBattleOption ( int option )
{
    switch ( option )
    {
        case 1:
            fight();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
    }
}

void Encounter_Base :: fight ()
{
    int move = getMove();

    std::cout << "move chosen" << std::endl;

    Game::pressEnterToContinue();
}

unsigned Encounter_Base :: getMove ()
{
    printMoveOptions();
    int option =  getBattleOption( 1, m_p_playerAsciimon->getMoves().size() + 1,
                                   std::bind( &Encounter_Base::printMoveOptions, this ) );
    if ( option == m_p_playerAsciimon->getMoves().size() + 1 ) input();

    return option;
}

void Encounter_Base :: printInitOptions ()
{
    Game::printLine( "Pick 1-4 " );
    Game::printLine( "1. Fight!" );
    Game::printLine( "2. Switch!" );
    Game::printLine( "3. Item!" );
    Game::printLine( "4. Run!" );
}

void Encounter_Base :: printMoveOptions ()
{
    std::cout << "Which move?" << std::endl;

    for ( size_t i = 0 ; i <  m_p_playerAsciimon->getMoves().size() ; i++ )
    {
        std::cout << i << ". " << m_p_playerAsciimon->getMoves().at( i ).getInfo().name << std::endl;
    }

    std::cout << m_p_playerAsciimon->getMoves().size() << ". Back." << std::endl;
}


















}
