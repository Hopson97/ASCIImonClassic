#ifndef GAME_H
#define GAME_H

#include "States/handler.h"
#include "player.h"

class Game_Main
{
    State::Handler  m_states;
    Player          m_player;
    bool            m_isRunning = true;

    public:
        Game_Main   ();

        void runLoop                ();

        State::Handler& getStates   ();

        Player&  getPlayer  ();

        void stopRunning    ();

        void save           ();

        void setRedrawNeeded();

    private:
        bool saveIfClosed   ();

        bool m_isRedrawNeeded;


};

#endif // GAME_H
