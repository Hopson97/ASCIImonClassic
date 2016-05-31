#ifndef HANDLER_H
#define HANDLER_H

#include <stack>

#include "b_state.h"

/**
    State::Handler handles all the states that will be used by the main "Game" class
*/

namespace State
{

class Handler
{
    std::stack<State_Base*> m_states;

    public:
        ~Handler();

        void
        changeState ( State_Base* state);

        void
        pushState   ( State_Base* state );

        void
        popState        ();

        State_Base*
        peekState       ();


        std :: size_t
        size            () const;
};

}

#endif // HANDLER_H
