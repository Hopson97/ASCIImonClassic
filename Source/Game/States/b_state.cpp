#include "b_state.h"

#include <iostream>

#include "../game.h"
#include "game_funcs.h"
#include "../../Utilities/console_funcs.h"
#include "../../Utilities/keyboard.h"

/**
    The base class for all the games states, such as menus, roaming, battles etc
*/

#include "asciimon_evolver.h"

namespace State
{

State_Base :: State_Base ( Game_Main& game)
    :   m_game   ( game )
{ }



Game_Main& State_Base :: getGame ()
{
    return m_game;
}



Player& State_Base :: getPlayer ()
{
    return m_game.getPlayer();
}



const Input_Movement_Keys& State_Base :: getInputKeyMovement () const
{
    return m_movementInputKeys;
}

void State_Base :: drawInputs ()
{
    Console::clear();
    std::cout << "Up:    " << m_movementInputKeys.moveUp    << std::endl;
    std::cout << "Down:  " << m_movementInputKeys.moveDown  << std::endl;
    std::cout << "Left:  " << m_movementInputKeys.moveLeft  << std::endl;
    std::cout << "Right: " << m_movementInputKeys.moveRight << std::endl;
}

void State_Base :: changeInputKeys ()
{
    Console::setTextColour( Console::Foreground_Colour::WHITE );
    std::string question = "What do you want the input for ";

    drawInputs();
    std::cout << question << "up? ";
    m_movementInputKeys.moveUp = Keyboard::waitForKey();

    Keyboard::waitForNoKey();

    drawInputs();
    std::cout << question << "down? ";
    m_movementInputKeys.moveDown = Keyboard::waitForKey();

    Keyboard::waitForNoKey();

    drawInputs();
    std::cout << question << "left? ";
    m_movementInputKeys.moveLeft = Keyboard::waitForKey();

    Keyboard::waitForNoKey();

    drawInputs();
    std::cout << question << "right? ";
    m_movementInputKeys.moveRight = Keyboard::waitForKey();
}

void State_Base :: checkForEvolve ( Asciimon& asciimon )
{
    if ( asciimon.canEvolve() )
    {
        auto id = asciimon.getEvolveId();

        Asciimon_Evolver evolver ( asciimon, id );
        evolver.evolve();
    }
}

}
