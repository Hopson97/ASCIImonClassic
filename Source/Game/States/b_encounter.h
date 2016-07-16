#ifndef ENCOUNTER_BASE_H
#define ENCOUNTER_BASE_H


#include "game.h"
#include "b_state.h"
#include "asciimon.h"

#include <memory>

namespace State
{

class Encounter_Base : public State_Base
{
    public:
        Encounter_Base          ( Game_Main& game );

        void input      () override;

        void update     () override;

        void draw       () override;

    protected:
        virtual void initEncounter () = 0;

        void haveTurn           ();
        void setEnemy           ( Asciimon& asciimon );

        Asciimon* m_p_playerAsciimon = nullptr;
        Asciimon* m_p_enemyAsciimon = nullptr;
};

}


#endif // ENCOUNTER_BASE_H
