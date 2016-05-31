#include "b_state.h"

#include "../game.h"

/**
    The base class for all the games states, such as menus, roaming, battles etc
*/

namespace State
{

State_Base :: State_Base ( Game_Main& game)
:   m_game   ( game )
{ }

Game_Main&
State_Base :: getGame ()
{
    return m_game;
}

const Input_Movement_Keys&
State_Base :: getInputKeyMovement () const
{
    return m_movementInputKeys;
}

}
