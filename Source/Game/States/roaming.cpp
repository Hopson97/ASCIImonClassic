#include "States/roaming.h"

#include <conio.h>
#include <iostream>

#include "keyboard.h"
#include "console_funcs.h"
#include "game_funcs.h"
#include "d_tiles.h"
#include "random_functions.h"

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
    else if ( key == 'e' )
    {
        getGame().stopRunning();
    }
    else if ( key == 'c')
    {
        changeInputKeys ();
    }
}


void
Roaming :: update ()
{
    if ( m_nextMove )
    {
        checkForBlock   ();
        checkForWater   ();
        checkForMapMove ();
        checkForPortal  ();

        movePlayer( m_nextMove );

        testForEncounter();
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

//Encounter code begins by testing if an encounter will happen
//And then it tests for which ASCIImon to attack
//And then changes the game state
void
Roaming :: testForEncounter ()
{
    if ( !testForEncounterTile() ) return;

    constexpr static int annoyenceReductionMultiplier = 7;  //Lessens the chance of an encounter by increasing
                                                            //the "chance bounds" thus reducing the "asciimon bounds"
    int total = m_map.getTotalAsciimonWeight();
    int chance = Random::integer( 0, total * annoyenceReductionMultiplier );

    if ( chance > total - 1 ) return;
    else
        startEncounter( chance );
}

//Checks if the tile being stood on is a tile that has potential to have an encounter eg long grass
bool
Roaming :: testForEncounterTile ()
{
    for ( auto& tile : Tiles::encounterTiles )
    {
        if ( tile == getTileAtPlayerCurrLocation() )
            return true;
    }
    return false;
}


#define FAILURE -1

void
Roaming :: startEncounter ( const int chance )
{

    int id = getAsciimonIdToEncounter( chance );

    if ( id == FAILURE ) return;
}


/*  Gets the ASCIImon ID of the ASCIImon to encounter, which takes two steps:

    Step One:
        We need to get the bounds of the map's encounterable ASCIImons' weights, and create
        a lower/ upper bound structure.
        Eg, if three have weights 4, 5, and 8, then the structure will be
        0 3
        4 4
        5 7
        With the "chance" somewhere between those bounds, and each bound has an attached id with it
        as seen in the struct above.

    Step Two:
        The bounds are simply checked against the bounds until the correct ASCIImon is found
*/
int
Roaming :: getAsciimonIdToEncounter ( const int chance )
{
    struct Potential_ASCIImon
    {
        int lowerBound;
        int upperBound;
        int id;
    };
    std::vector<Potential_ASCIImon> potentialAsciimon;

    //Step One:
    int total = 0;
    for ( auto& asciimon : m_map.getEncounterableAsciimon() )
    {
        potentialAsciimon.push_back( {  total,
                                        total + asciimon.getWeight() - 1,
                                        asciimon.getId() } );
        total += asciimon.getWeight();
    }

    //Step Two:
    for ( auto& asciimon : potentialAsciimon )
    {
        if ( asciimon.lowerBound <= chance &&
            asciimon.upperBound >= chance )
        {
            return asciimon.id;
        }
    }
    return FAILURE; //If this messes up somehow, then it returns an error number.
}

#undef FAILURE


//Moves the player in the field
void
Roaming :: movePlayer  ( const Vector2i& amount )
{
    isUpdateNeeded = true;
    getPlayer().moveInField( amount );
}

//Checks for if where the player is about to go is a "block" tile (non-passable)
void
Roaming :: checkForBlock   ()
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
void
Roaming :: checkForWater()
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
void
Roaming :: checkForMapMove ()
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
void
Roaming :: checkForPortal ()
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


char
Roaming :: getTileAtPlayerNextLocation ()
{
    return m_map.at( getPlayer().
                     getFieldLocation() + m_nextMove );
}


char
Roaming :: getTileAtPlayerCurrLocation ()
{
    return m_map.at( getPlayer().getFieldLocation() );
}


/*  After going through a move tile, the map will change, thus the player must move to a different location
    in the field depending on the direction
    of map movement
*/
void
Roaming :: setPlayerPosAfterMapMove ( const char tile )
{
    const Vector2i& playerPosition = getPlayer().getFieldLocation();

    if ( tile == '>' )
    {
        getPlayer().setFieldPosition( { 2, playerPosition.y } );
    }
    else if ( tile == '<' )
    {
        getPlayer().setFieldPosition( { m_map.getSize().x - 2, playerPosition.y } );
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
