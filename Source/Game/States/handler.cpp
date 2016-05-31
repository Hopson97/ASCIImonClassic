#include "handler.h"

/**
    State::Handler handles all the states that will be used by the main "Game" class
*/

namespace State
{

Handler :: ~Handler ()
{
    while ( !m_states.empty() ) {
        popState();
    }
}



void
Handler :: changeState ( State_Base* state)
{
    if( !m_states.empty() ) {;
        popState();
    }
    m_states.push ( state  );
}



void
Handler :: pushState ( State_Base* state )
{
    m_states.emplace ( state );
}



void
Handler :: popState ()
{
    if( !m_states.empty() ) {
        delete m_states.top();
        m_states.pop();
    }
}



State_Base*
Handler :: peekState ()
{
    return m_states.top() ;
}

std :: size_t
Handler :: size () const
{
    return m_states.size();
}

}
