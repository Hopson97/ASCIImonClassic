#ifndef ROAMING_H
#define ROAMING_H

#include "../game.h"
#include "b_state.h"

#include "../Maths/vector2.h"

#include "../Map/map.h"
#include "../../Loaders/map_loader.h"

namespace State
{

class Roaming : public State_Base
{
    public:
        Roaming         ( Game_Main& game, const Vector2i& mapLocation );

        void input      () override;

        void update     () override;

        void draw       () override;

    private:
        void testForWildEncounter           ();

        bool testForWildEncounterTile       ();

        void startWildEncounter             ( unsigned chance );

        unsigned getWildAsciimonIdToEncounter    ( unsigned chance, unsigned& level );



        void movePlayer         ( const Vector2i& amount );

        void checkForBlock      ();

        void checkForWater      ();

        void checkForMapMove    ();

        void checkForPortal     ();

        char getTileAtPlayerNextLocation    ();

        char getTileAtPlayerCurrLocation    ();

        char getTileAtPlayerDirection       ();


        void setPlayerPosAfterMapMove       ( const char tile );

        Map m_map;
        Map_Loader  m_mapLoader;

        Vector2i    m_nextMove;
};

}

#endif // ROAMING_H
