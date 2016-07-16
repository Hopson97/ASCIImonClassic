#ifndef ENCOUNTER_BASE_H
#define ENCOUNTER_BASE_H


#include "game.h"
#include "b_state.h"
#include "asciimon.h"

#include <memory>
#include <functional>

namespace State
{

class Encounter_Base : public State_Base
{
    enum Turn_Type
    {

    };


    public:
        Encounter_Base  ( Game_Main& game );

        void input      () override;

        void update     () override;

        void draw       () override;

    protected:
        virtual void initEncounter () = 0;

        void haveTurn           ();

        Asciimon* m_p_playerAsciimon = nullptr;
        Asciimon* m_p_enemyAsciimon  = nullptr;

    private:
        void drawHealthBar  ( const Asciimon& asciimon ) const;
        void drawName       ( const Asciimon& asciimon ) const;

        void invalidInput   ();

        void printInitOptions   ();
        void printMoveOptions   ();

        int getBattleOption     ( int min, int max, std::function<void(void)> failSafe );

        void gotoBattleOption   ( int option );

        void fight          ();
        unsigned getMove    ();
};

}


#endif // ENCOUNTER_BASE_H
