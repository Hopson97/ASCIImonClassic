#include "game.h"

#include "States/roaming.h"
#include "clock.h"

Game_Main :: Game_Main ()
{
    m_states.pushState( new State::Roaming( *this, {0, 0 } ) );
}

void
Game_Main :: runLoop ()
{
    Clock m_clock;
    double timeFrame = 0.2; //Fixed time between updates, inputs and draws

    while ( m_isRunning )
    {
        m_states.peekState()->input ();

        if ( saveIfClosed() )
            break;

        m_states.peekState()->update();

        if ( saveIfClosed() )
            break;

        m_states.peekState()->draw  ();

        if ( saveIfClosed() )
            break;

        while ( m_clock.getCurrentTime() < timeFrame );
        m_clock.restart();
    }
}

State::Handler&
Game_Main :: getStates ()
{
    return m_states;
}

Player&
Game_Main :: getPlayer ()
{
    return m_player;
}

void
Game_Main :: stopRunning ()
{
    m_isRunning = false;
}

void
Game_Main :: save ()
{

}

bool
Game_Main :: saveIfClosed ()
{
    if ( !m_isRunning )
    {
        save();
        return true;
    }
    return false;
}
