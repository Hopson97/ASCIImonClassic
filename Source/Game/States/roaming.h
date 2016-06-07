#ifndef ROAMING_H
#define ROAMING_H

#include "game.h"
#include "States/b_state.h"

#include "Maths/vector2.h"

#include "map.h"
#include "map_loader.h"

namespace State
{

class Roaming : public State_Base
{
    Map m_map;
    Map_Loader  m_mapLoader;

    Vector2i    m_nextMove;

    public:
        Roaming                     ( Game_Main& game, const Vector2i& mapLocation );

        void
        input                       () override;

        void
        update                      () override;

        void
        draw                        () override;

    private:
        void
        movePlayer                  ( const Vector2i& amount );

        void
        checkForBlock               ();

        void
        checkForMapMove             ();

        void
        checkForPortal              ();

        char
        getTileAtPlayerLocation     ();

        void
        setPlayerPosAfterMapMove    ( const char tile );
};

}

#endif // ROAMING_H
