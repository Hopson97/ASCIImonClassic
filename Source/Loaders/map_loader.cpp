#include "map_loader.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include "t_casts.h"
#include "d_tiles.h"

const std::string fileType      = "Map File (.map)";
const std::string mapLocation   = "Data/Maps/";

const std::string mapSection    = "MAP";
const std::string portalSection  = "PORTAL";

int portalsRead = 0;

void
Map_Loader :: load ( Map* p_map )
{
    m_p_map = p_map;

    m_p_map->m_currentArea.clear();
    m_p_map->m_size.reset();
    m_p_map->m_portals.clear();
    portalsRead = 0;

    readFile( fileType );
}

void
Map_Loader :: checkLine ()
{
    if ( checkForWord( mapSection ) )
        readMapChars();
    else if ( checkForWord( portalSection ) )
        readPortal();
    else
        throwUnrecognisedWord();
}

void
Map_Loader :: readMapChars ()
{
    while ( !endOfSection() )
    {
        m_p_map->m_currentArea.append( getCurrentLineString() );

        countPortalsOnLine();

        m_p_map->m_size.x =  getCurrentLineString().length();
        m_p_map->m_size.y += 1;
    }
}

void
Map_Loader :: countPortalsOnLine  ()
{
    for ( int x = 0 ; (unsigned)x < getCurrentLineString().length() ; x++ )
    {
        for ( auto& t : Tiles::portals )
        {
            if ( getCurrentLineString().at( (unsigned)x ) == t.first )
            {
                int y = m_p_map->m_size.y;
                m_p_map->m_portals.push_back( Portal( { x, y } ) );
            }
        }
    }
}

void
Map_Loader :: readPortal ()
{
    const static std::string goesToSection          = "GOES TO";
    const static std::string playerStandsSection    = "PLAYER STANDS";

    Vector2i goesTo;
    Vector2i stands;

    while ( !endOfSection() )
    {
        if ( checkForWord( goesToSection ) )
        {
            goesTo = readVector2i();
        }
        else if ( checkForWord( playerStandsSection ) )
        {
            stands = readVector2i();
        }
        else
            throwUnrecognisedWord();
    }
    m_p_map->m_portals.at( portalsRead++ ).setUp( goesTo, stands );
}


const std::string
Map_Loader :: getFileName () const
{
    Vector2i location = m_p_map->m_location;

    return  mapLocation +
            Convert::toString( location.x ) + " " +
            Convert::toString( location.y ) + ".map";
}


