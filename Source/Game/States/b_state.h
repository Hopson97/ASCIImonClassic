#ifndef STATE_BASE_H
#define STATE_BASE_H

/**
    The base class for all the games states, such as menus, roaming, battles etc
*/

#include "asciimon.h"

class Player;
class Game_Main;

struct Input_Movement_Keys
{
    char moveUp     = 'w';
    char moveDown   = 's';

    char moveLeft   = 'a';
    char moveRight  = 'd';
};

namespace State
{

class State_Base
{
    Game_Main&              m_game;
    Input_Movement_Keys     m_movementInputKeys;

    public:
        State_Base              ( Game_Main& game);
        virtual ~State_Base     ()   {}

        virtual void input      () = 0;

        virtual void update     () = 0;

        virtual void draw       () = 0;

        void drawInputs         ();

        void changeInputKeys    ();

        void checkForEvolve     ( Asciimon& asciimon );

    protected:

        Game_Main& getGame      ();

        Player& getPlayer       ();

        const Input_Movement_Keys& getInputKeyMovement    () const;
};

}

#endif // STATE_BASE_H
