#ifndef NEW_GAME_H
#define NEW_GAME_H

#include "b_state.h"
#include "game.h"

namespace State
{

class New_Game : public State_Base
{
    public:
        New_Game( Game_Main& game );

        void input  () override;
        void update () override;
        void draw   () override;

    private:
        void getName( std::string& name );

        void printAsciimnStarters () const;
        void invalid();

        std::vector<Asciimon*> m_asciimon;

        Asciimon grass;
        Asciimon water;
        Asciimon fire;
};

}

#endif // NEW_GAME_H
