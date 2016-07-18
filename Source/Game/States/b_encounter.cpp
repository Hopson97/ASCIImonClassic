#include "b_encounter.h"

#include "percentage_bar.h"
#include "general_funcs.h"
#include "game_funcs.h"
#include "t_casts.h"
#include "keyboard.h"
#include "animated_text.h"
#include "console_funcs.h"
#include "sound_manager.h"
#include "Music_Manager.h"

#include <iostream>

const int BACK_MOVE = 10;

namespace State
{

Encounter_Base :: Encounter_Base ( Game_Main& game )
    :   State_Base ( game )
{

}


void Encounter_Base :: input()
{
    printInitOptions();
    int option = General::getInput( 1, 4, std::bind( &Encounter_Base::printInitOptions, this ),
                                    std::bind( &Encounter_Base::invalidInput, this) );
    gotoBattleOption( option );
    if ( m_move == BACK_MOVE ) input();
}

void Encounter_Base :: update()
{
    const bool enemyIsFaster =  (   getEnemyAsciimon().getStat ( Stat_Name::Speed ).getCurrValue() >
                                    getPlayerAsciimon().getStat( Stat_Name::Speed ).getCurrValue() );

    if ( enemyIsFaster ) Encounter_Base::enemyTurn();


    switch ( m_turnType )
    {
    case Turn_Type::Fight:
        fightTurn();
        break;
    }

    if ( getEnemyAsciimon().isFainted() )
    {
        Encounter_Base::enemyFainted();
        return;
    }

    if ( !enemyIsFaster ) Encounter_Base::enemyTurn();
}

void Encounter_Base :: draw()
{
    drawName        ( getEnemyAsciimon() );
    getEnemyAsciimon().printLevel();
    drawHealthBar   ( getEnemyAsciimon() );
    getEnemyAsciimon().drawFront();

    Console::newLine();
    Game::printLine( "-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_");
    Console::newLine();

    getPlayerAsciimon().drawBack();
    drawName        ( getPlayerAsciimon() );
    getPlayerAsciimon().printHealth();
    drawHealthBar   ( getPlayerAsciimon() );
    getPlayerAsciimon().printLevel();
    drawExpAndBar();
}

void Encounter_Base :: enemyTurn ()
{
    enemyTurn();
    if ( getPlayerAsciimon().isFainted() )
    {
        playerFainted();
    }
}

void Encounter_Base :: enemyFainted ()
{
    Console::clear();

    Animated_Text::quickTextCol( "The enemy " + getEnemyAsciimon().getName() + " has fainted!",
                                 getEnemyAsciimon().getFrontImage(),
                                 0.05,
                                 getEnemyAsciimon().getTypeColour() );

    auto exp = getEnemyAsciimon().getFaintExp();

    Game::message( getPlayerAsciimon().getName() + " gains " + Convert::toString(exp) + " exp!");

    getPlayerAsciimon().addExp( exp );

    if ( getPlayerAsciimon().canLevelUp() )
    {
        State_Base::checkForEvolve( getPlayerAsciimon() );
    }
    enemyFainted();
}

void Encounter_Base :: playerFainted ()
{
    ///rip
}

void Encounter_Base :: attack ( Asciimon& attacker, Asciimon& defender, Asciimon_Move& move, bool isPlayer )
{
    Console::clear();
    std::string identity;

    if ( isPlayer) identity = "Your " + getPlayerAsciimon().getName();
    else identity =  "The enemy ";
    Animated_Text::quickTextCol(  identity + " used " + move.getInfo().name + "!",
                                  attacker.getFrontImage(),
                                  0.05,
                                  attacker.getTypeColour() );

    if ( defender.hit( attacker, move ) )
    {
        Game::shortPause( 0.3 );

        Console::clear();

        Console::setTextColour( Console::Foreground_Colour::RED );
        defender.drawFront( false );
        Game::shortPause( 0.1 );
        Console::resetColours();

        Console::clear();

        defender.drawFront();
        Game::shortPause( 0.2 );

        move.use();

        Game::pressEnterToContinue();
    }
    else
    {
        Animated_Text::quickTextCol(  identity + " missed! ", attacker.getFrontImage(), 0.05,
                                      attacker.getTypeColour() );
    }
}

void Encounter_Base :: fightTurn()
{
    attack( getPlayerAsciimon(), getEnemyAsciimon(), getPlayerAsciimon().getMove( m_move ), true );
}

Asciimon& Encounter_Base :: getPlayerAsciimon ()
{
    return *m_p_playerAsciimon;
}

Asciimon& Encounter_Base :: getEnemyAsciimon ()
{
    return *m_p_enemyAsciimon;
}

const Asciimon& Encounter_Base :: getPlayerAsciimon () const
{
    return *m_p_playerAsciimon;
}

const Asciimon& Encounter_Base :: getEnemyAsciimon  () const
{
    return *m_p_enemyAsciimon;
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

void Encounter_Base :: drawExpAndBar  () const
{
    Percentage_Bar bar;

    bar.draw( getPlayerAsciimon().getLevel().getCurrentExp(),
              getPlayerAsciimon().getLevel().getExpForNextLevel(),
              Console::Foreground_Colour::BLUE,
              Console::Foreground_Colour::GRAY
            );
}

void Encounter_Base :: drawName ( const Asciimon& asciimon ) const
{
    std::cout << asciimon.getName() << std::endl;
}

void Encounter_Base :: invalidInput   ()
{
    Console::clear();
    Console::printInvalidInput();
    getGame().setRedrawNeeded();
    draw();
}

void Encounter_Base :: gotoBattleOption ( int option )
{
    switch ( option )
    {
    case 1:
        fightInput();
        break;
    case 2:
        break;
    case 3:
        tryCatch();
        break;
    case 4:
        tryRun();
        break;
    }
}

void Encounter_Base :: endBattle ()
{
    Game::printToLog( "Wild Encounter End" );
    Music_Manager::popSong();
    getGame().getStates().popState();
}

void Encounter_Base :: fightInput ()
{
    m_move = getMove() - 1;

    if ( m_move == Asciimon_Move::MAX_MOVES + 1 )
    {
        m_move = BACK_MOVE;
        return;
    }

    m_turnType = Turn_Type::Fight;


}

unsigned Encounter_Base :: getMove ()
{
    printMoveOptions();
    unsigned option = General::getInput( 1, getPlayerAsciimon().getMoves().size() + 1,
                                         std::bind( &Encounter_Base::printMoveOptions, this ),
                                         std::bind( &Encounter_Base::invalidInput, this) );

    if ( option == getPlayerAsciimon().getMoves().size() + 1 ) return Asciimon_Move::MAX_MOVES + 2;

    return option;
}

void Encounter_Base :: printInitOptions ()
{
    redrawScene();
    Game::printLine( "Pick 1-4 " );
    Game::printLine( "1. Fight!" );
    Game::printLine( "2. Switch!" );
    Game::printLine( "3. Item!" );
    Game::printLine( "4. Run!" );
}

void Encounter_Base :: printMoveOptions ()
{
    redrawScene();
    std::cout << "Which move?" << std::endl;

    for ( size_t i = 0 ; i <  getPlayerAsciimon().getMoves().size() ; i++ )
    {
        std::cout << i + 1 << ". " << getPlayerAsciimon().getMoves().at ( i ).getInfo().name << " ";
        getPlayerAsciimon().getMoves().at( i ).printStatus();
        Console::newLine();
    }

    std::cout << getPlayerAsciimon().getMoves().size() + 1 << ". Back." << std::endl;
}

void Encounter_Base :: redrawScene ()
{
    Console::clear();
    getGame().setRedrawNeeded();
    draw();
}
















}
