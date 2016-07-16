#include "game.h"

#include "States/roaming.h"
#include "States/new_game.h"
#include "../Utilities/clock.h"
#include "console_funcs.h"

Game_Main :: Game_Main ()
{
    m_states.pushState( new State::Roaming( *this, {0, 0 } ) );
    //m_states.pushState( new State::New_Game ( *this ) );
}


void Game_Main :: runLoop ()
{
    Clock m_clock;
    double timeFrame = 0.2; //Fixed time between updates, inputs and draws

    while ( m_isRunning )
    {
        m_states.peekState()->input ();

        m_states.peekState()->update();


        if ( m_isRedrawNeeded )
        {
            Console::clear();
            m_states.peekState()->draw ();
            m_isRedrawNeeded = false;
        }



        while ( m_clock.getCurrentTime() < timeFrame );
        m_clock.restart();
    }
}


State::Handler& Game_Main :: getStates ()
{
    m_isRedrawNeeded = true;//Chances are, if the states are being got then the states are about to change
    return m_states;
}


Player& Game_Main :: getPlayer ()
{
    return m_player;
}


void Game_Main :: stopRunning ()
{
    m_isRunning = false;
}


void Game_Main :: save ()
{

}


void Game_Main :: setRedrawNeeded()
{
    m_isRedrawNeeded = true;
}


bool Game_Main :: saveIfClosed ()
{
    if ( !m_isRunning )
    {
        save();
    }
    return !m_isRunning;
}
