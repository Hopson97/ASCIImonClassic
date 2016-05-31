#include "States/roaming.h"

#include <conio.h>
#include <iostream>

#include "keyboard.h"
#include "console_funcs.h"

bool isUpdateNeeded = true;



namespace State
{

Roaming :: Roaming ( Game_Main& game, const Vector2i& mapLocation )
:   State_Base  ( game )
,   m_map       ( mapLocation.x, mapLocation.y )
{
    m_mapLoader.load( &m_map );
}

void
Roaming :: input ()
{
    m_nextMove.reset();
    char key = Keyboard::getKey();

    if ( key == getInputKeyMovement().moveUp )
    {
        m_nextMove = { 0, -1 };
    }
    else if ( key == getInputKeyMovement().moveLeft )
    {
        m_nextMove = { -1, 0 };
    }
    else if ( key == getInputKeyMovement().moveRight )
    {
        m_nextMove =  { 1, 0 };
    }
    else if ( key == getInputKeyMovement().moveDown )
    {
        m_nextMove =  { 0, 1 };
    }
}

void
Roaming :: update ()
{
    if ( !m_nextMove ) return;

    for ( auto& block : m_map.getBlockTiles() )
    {
        if ( m_map.at( getGame().getPlayer().
                       getFieldLocation() + m_nextMove )
            == block )
        {
            m_nextMove.reset();
            break;
        }
    }

    movePlayer( m_nextMove );
}

void
Roaming :: draw ()
{
    if ( isUpdateNeeded )
    {
        Console::clear();
        m_map.draw( getGame().getPlayer().getFieldLocation() );
    }

    isUpdateNeeded = false;
}

void
Roaming :: movePlayer  ( const Vector2i& amount )
{
    isUpdateNeeded = true;
    getGame().getPlayer().moveInField( amount );
    return;
}


}
