#include "map_loader.h"

#include <stdexcept>
#include <string>
#include <iostream>

#include "../Utilities/t_casts.h"
#include "../Game/Map/d_tiles.h"

const std::string fileType              =   "Map File (.map)";
const std::string mapLocation           =   "Data/Maps/";

const std::string nameSection           =   "NAME";
const std::string mapSection            =   "MAP";
const std::string portalSection         =   "PORTAL";
const std::string encrAsciimonSection   =   "ASCIIMON";

int portalsRead = 0;

Map_Loader :: Map_Loader ()
{
    addKeyword( std::bind ( &Map_Loader::getName,                   this ), nameSection );
    addKeyword( std::bind ( &Map_Loader::readMapChars,              this ), mapSection );
    addKeyword( std::bind ( &Map_Loader::readPortal,                this ), portalSection );
    addKeyword( std::bind ( &Map_Loader::readEncounterableAsciimon, this ), encrAsciimonSection );
}

void Map_Loader :: load ( Map* p_map )
{
    m_p_map = p_map;

    m_p_map->m_portals.clear();
    m_p_map->m_currentArea.clear();
    m_p_map->m_encounterableASCIImon.clear();

    m_p_map->m_size.reset();
    portalsRead = 0;

    readFile( fileType );
}

void Map_Loader :: getName ()
{
    Loader_Base::readLine();
    m_p_map->m_currentAreaName = getCurrentLineString();
    readLine();
}

void Map_Loader :: readMapChars ()
{
    while ( !endOfSection() )
    {
        m_p_map->m_currentArea.append( getCurrentLineString() );

        countPortalsOnLine();

        m_p_map->m_size.x =  getCurrentLineString().length();
        m_p_map->m_size.y += 1;
    }
}

void Map_Loader :: countPortalsOnLine  ()
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



void Map_Loader :: readPortal ()
{
    const static std::string goesToSection          = "GOES TO";
    const static std::string playerStandsSection    = "PLAYER STANDS";

    Vector2i goesTo;
    Vector2i stands;

    while ( !endOfSection() )
    {
        if ( checkForWord( goesToSection ) )
        {
            readVector2i( goesTo );
        }
        else if ( checkForWord( playerStandsSection ) )
        {
            readVector2i( stands );
        }
        else
            throwUnrecognisedWord();
    }
    m_p_map->m_portals.at( portalsRead++ ).setUp( goesTo, stands );
}


void Map_Loader :: readEncounterableAsciimon ()
{
    const static std::string idSection      = "ID";
    const static std::string weightSection  = "WEIGHT";

    int id      = -1;
    int weight  = -1;

    while ( !endOfSection() )
    {
        if ( checkForWord( idSection ) )
        {
            readNumber  ( id );
        }
        else if ( checkForWord ( weightSection ) )
        {
            readNumber ( weight );
        }
    }

    m_p_map->m_encounterableASCIImon.emplace_back( id, weight );
}



const std::string Map_Loader :: getFileName () const
{
    //Short hand
    const Vector2i& location = m_p_map->m_location;

    return  mapLocation +
            Convert::toString( location.x ) + " " +
            Convert::toString( location.y ) + ".map";
}


