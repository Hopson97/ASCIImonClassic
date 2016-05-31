#include "map_loader.h"

#include <stdexcept>
#include <string>

#include <t_casts.h>

const std::string fileType      = "Map File (.map)";
const std::string mapLocation   = "Data/Maps/";

const std::string mapSection    = "MAP";

void
Map_Loader :: load ( Map* p_map )
{
    m_p_map = p_map;
    m_p_map->m_currentArea.clear();
    m_p_map->m_size = { 0, 0 };
    readFile( fileType );
}

void
Map_Loader :: checkLine ()
{
    if ( checkForWord( mapSection ) )
        readMapChars();
    else
        std::runtime_error ( "Found unknown word: " +
                             getCurrentLineString() +
                            ", terminating program.");
}

void
Map_Loader :: readMapChars ()
{
    readLine();
    while ( !endOfSection() )
    {
        m_p_map->m_size.x =  getCurrentLineString().length();
        m_p_map->m_size.y += 1;

        m_p_map->m_currentArea.append( getCurrentLineString() );


        readLine();
    }
}


const std::string
Map_Loader :: getFileName () const
{
    Vector2i location = m_p_map->m_location;

    return  mapLocation +
            Convert::toString( location.x ) + " " +
            Convert::toString( location.y ) + ".map";
}


