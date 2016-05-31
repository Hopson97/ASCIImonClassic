#include "map.h"

#include <iostream>

#include "console_funcs.h"
#include "gv_update.h"

constexpr short areaVisible = 6;

Map :: Map( const int x, const int y )
:   m_location  ( x, y )
{ }

void
Map :: draw ( const Vector2i& fieldLocation )
{
    Console::printTenBlankLines();

    int xStart = fieldLocation.x - areaVisible + 1;
    int xEnd   = fieldLocation.x + areaVisible;

    int yStart = fieldLocation.y - areaVisible + 1;
    int yEnd = fieldLocation.y   + areaVisible;

    if ( xStart < 0 )
        xStart = 0;
    if ( xEnd > m_size.x)
        xEnd = m_size.x;

    if ( yStart < 0 )
        yStart = 0;
    if ( yEnd > m_size.y)
        yEnd = m_size.y;

    for ( int y = yStart ; y < yEnd ; y++ )
    {
        Console::lineStartSpace();

        for ( int x = xStart ; x < xEnd ; x++ )
        {
            char currentTile = at( x, y );

            if ( x == fieldLocation.x && y == fieldLocation.y )
            {
                currentTile = '@';
            }

            std::cout << currentTile << " ";
        }
        Console::newLine();
    }
}

char
Map :: at ( const int x, const int y) const
{
    return m_currentArea.at( ( y * m_size.x ) + x );
}

char
Map :: at ( const Vector2i& location ) const
{
    return at ( location.x, location.y );
}

const std::vector<char>&
Map :: getBlockTiles () const
{
    return m_blockTiles;
}
