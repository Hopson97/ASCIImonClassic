#include "roaming.h"

#include <conio.h>
#include <iostream>

#include "../../Utilities/keyboard.h"
#include "../../Utilities/console_funcs.h"
#include "../../Utilities/random_functions.h"

#include "../game_funcs.h"
#include "../Map/d_tiles.h"

namespace State
{

Roaming :: Roaming ( Game_Main& game, const Vector2i& mapLocation )
:   State_Base  ( game )
,   m_map       ( mapLocation.x, mapLocation.y )
{
    m_mapLoader.load( &m_map );
}

void Roaming :: input ()
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
    else if ( key == 'e' )
    {
        getGame().stopRunning();
    }
    else if ( key == 'c')
    {
        changeInputKeys ();
    }
}


void Roaming :: update ()
{
    if ( m_nextMove )
    {
        checkForBlock   ();
        checkForWater   ();
        checkForMapMove ();
        checkForPortal  ();

        movePlayer( m_nextMove );

        testForWildEncounter();
    }
}


void Roaming :: draw ()
{
    if ( isUpdateNeeded )
    {
        Console::clear();
        m_map.draw( getPlayer().getFieldLocation() );
    }

    isUpdateNeeded = false;
}


//Moves the player in the field
void Roaming :: movePlayer  ( const Vector2i& amount )
{
    isUpdateNeeded = true;
    getPlayer().moveInField( amount );
}

//Checks for if where the player is about to go is a "block" tile (non-passable)
void Roaming :: checkForBlock   ()
{
    for ( auto& tile : Tiles::blocks )
    {
        if ( getTileAtPlayerNextLocation() == tile )
        {
            m_nextMove.reset();
            break;
        }
    }
}

//Checks for if where the player is about to go is a "water" tile (non-passable if NOT SWIMMING)
void Roaming :: checkForWater()
{
    for ( auto& tile : Tiles::water )
    {
        if ( getTileAtPlayerNextLocation() == tile )
        {
            //Handle "Swimming" here maybe?
            m_nextMove.reset();
            break;
        }
    }
}

//Checks if the player is about to step on a "map move tile" and so moves the map
//if he/she does
void Roaming :: checkForMapMove ()
{
    for ( auto& tile : Tiles::mapMoves )
    {
        if ( getTileAtPlayerNextLocation() == tile.first )
        {
            m_map.moveMap            ( tile.second );
            m_mapLoader.load         ( &m_map );
            setPlayerPosAfterMapMove ( tile.first );
            break;
        }
    }
}


/*
    Checks for a portal in the tile where the player has stepped.
*/
void Roaming :: checkForPortal ()
{
    for ( auto& tile : Tiles::portals )
    {
        if ( getTileAtPlayerNextLocation() == tile.first )
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


char Roaming :: getTileAtPlayerNextLocation ()
{
    return m_map.at( getPlayer().
                     getFieldLocation() + m_nextMove );
}


char Roaming :: getTileAtPlayerCurrLocation ()
{
    return m_map.at( getPlayer().getFieldLocation() );
}


/*  After going through a move tile, the map will change, thus the player must move to a different location
    in the field depending on the direction
    of map movement
*/
void Roaming :: setPlayerPosAfterMapMove ( const char tile )
{
    const Vector2i& playerPosition = getPlayer().getFieldLocation();

    if ( tile == '>' )
    {
        getPlayer().setFieldPosition( { 0, playerPosition.y } );
    }
    else if ( tile == '<' )
    {
        getPlayer().setFieldPosition( { m_map.getSize().x - 1, playerPosition.y } );
    }
    else if ( tile == 'v' )
    {
        getPlayer().setFieldPosition( { playerPosition.x, 0 } );
    }
    else if ( tile == '^' )
    {
        getPlayer().setFieldPosition( { playerPosition.x, m_map.getSize().y - 1 } );
    }
}



}
