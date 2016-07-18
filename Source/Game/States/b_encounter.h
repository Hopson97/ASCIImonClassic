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
    enum class Turn_Type
    {
        Fight
    } m_turnType;



    public:
        Encounter_Base  ( Game_Main& game );

        void input      () override;

        void update     () override;

        void draw       () override;

    protected:
        virtual void initEncounter  () = 0;
        virtual void tryRun         () = 0;
        virtual void tryCatch       () = 0;
        virtual void enemyTurn      ();

        virtual void enemyFainted   ();
        void playerFainted  ();

        void endBattle      ();

        void attack ( Asciimon& attacker, Asciimon& defender, Asciimon_Move& move, bool isPlayer );

        void fightTurn  ();

        Asciimon* m_p_playerAsciimon = nullptr;
        Asciimon* m_p_enemyAsciimon  = nullptr;

        //Short-Hand/ neater
        Asciimon& getPlayerAsciimon ();
        Asciimon& getEnemyAsciimon  ();

        const Asciimon& getPlayerAsciimon () const;
        const Asciimon& getEnemyAsciimon  () const;

    private:
        void drawHealthBar  ( const Asciimon& asciimon ) const;
        void drawName       ( const Asciimon& asciimon ) const;
        void drawExpAndBar  () const;

        void invalidInput   ();

        void printInitOptions   ();
        void printMoveOptions   ();

        int getBattleOption     ( int min, int max, std::function<void(void)> failSafe );

        void gotoBattleOption   ( int option );

        void fightInput     ();
        unsigned getMove    ();

        void redrawScene    ();


        int m_move;
};

}


#endif // ENCOUNTER_BASE_H
