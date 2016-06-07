#include "States/roaming.h"

#include <conio.h>
#include <iostream>

#include "keyboard.h"
#include "console_funcs.h"
#include "game_funcs.h"
#include "d_tiles.h"

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
        std::cout << "left " << std::endl;
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
    else if ( key == 'e' )
    {
        getGame().stopRunning();
    }
}


void
Roaming :: update ()
{
    if ( m_nextMove )
    {
        checkForBlock   ();
        checkForMapMove ();
        checkForPortal  ();

        movePlayer( m_nextMove );
    }
}


void
Roaming :: draw ()
{
    if ( isUpdateNeeded )
    {
        Console::clear();
        m_map.draw( getPlayer().getFieldLocation() );
    }

    isUpdateNeeded = false;
}

//Moves the player in the field
void
Roaming :: movePlayer  ( const Vector2i& amount )
{
    isUpdateNeeded = true;
    getPlayer().moveInField( amount );
    return;
}

//Checks for if where the player is about to go is a "block" tile (non-passable)
void
Roaming :: checkForBlock   ()
{
    for ( auto& tile : Tiles::blocks )
    {
        if ( getTileAtPlayerLocation() == tile )
        {
            m_nextMove.reset();
            break;
        }
    }
}

//Checks if the player is about to step on a "map move tile" and so moves the map
//if he/she does
void
Roaming :: checkForMapMove ()
{
    for ( auto& tile : Tiles::mapMoves )
    {
        if ( getTileAtPlayerLocation() == tile.first )
        {
            m_map.moveMap            ( tile.second );
            m_mapLoader.load         ( &m_map );
            setPlayerPosAfterMapMove ( tile.first );
            break;
        }
    }
}

void
Roaming :: checkForPortal ()
{
    for ( auto& tile : Tiles::portals )
    {
        if ( getTileAtPlayerLocation() == tile.first )
        {
            const Portal& portal = m_map.
                                    getPortalAt( getPlayer().getFieldLocation()
                                                 + m_nextMove );

            m_map.setLocation( portal.getGoesTo() );
            getPlayer().setFieldPosition( portal.getPlayerStands() );
            m_nextMove.reset();
            m_mapLoader.load( &m_map );
        }
    }
}


char
Roaming :: getTileAtPlayerLocation ()
{
    return m_map.at( getPlayer().
                     getFieldLocation() + m_nextMove );
}


void
Roaming :: setPlayerPosAfterMapMove ( const char tile )
{
    Vector2i pos = getPlayer().getFieldLocation();

    if ( tile == '>' )
    {
        getPlayer().setFieldPosition( { 2, pos.y } );
    }
    else if ( tile == '<' )
    {
        getPlayer().setFieldPosition( { m_map.getSize().x - 2, pos.y } );
    }
    else if ( tile == 'v' )
    {

    }
    else if ( tile == '^' )
    {

    }
}



}
