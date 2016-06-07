#include "map.h"

#include <iostream>

#include "console_funcs.h"
#include "d_tiles.h"
#include "t_casts.h"

constexpr short areaVisible = 8;

Map :: Map( const int x, const int y )
:   m_location  ( x, y )
{ }

void
Map :: draw ( const Vector2i& fieldLocation )
{
    //Console::printTenBlankLines();

    int xStart;
    int xEnd;
    int yStart;
    int yEnd;

    getMapDrawStartAndEnd( fieldLocation,
                           xStart, yStart,
                           xEnd,   yEnd );

    for ( int y = yStart ; y < yEnd ; y++ )
    {
        //Console::lineStartSpace();

        for ( int x = xStart ; x < xEnd ; x++ )
        {
            char currentTile = at( x, y );

            if ( x == fieldLocation.x && y == fieldLocation.y )
            {
                currentTile = '@';
            }

            setTileColour( currentTile );
            std::cout << currentTile << " ";
        }
        Console::newLine();
    }
}


const Vector2i&
Map :: getLocation () const
{
    return m_location;
}


void
Map :: setLocation ( const Vector2i& location )
{
    m_location = location;
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


void
Map :: moveMap ( const Vector2i& amount )
{
    m_location.x += amount.x;
    m_location.y += amount.y;
}


const Vector2i&
Map :: getSize () const
{
    return m_size;
}


const Portal&
Map :: getPortalAt ( const Vector2i& location ) const
{
    for ( auto& portal : m_portals )
    {
        if ( portal.getLocation() == location )
        {
            return portal;
        }
    }
    throw std::runtime_error ( "Portal not found at location: " +
                              Convert::toString( location.x )   +
                              " " +
                              Convert::toString( location.y ) );
}


void
Map :: setTileColour ( const char tile )
{
    try
    {
        Console::setTextColour( Tiles::colours.at( tile ) );
    }
    catch (const std::out_of_range& e)
    {
        Console::setTextColour( Console::Foreground_Colour::WHITE);
    }
}

void
Map :: getMapDrawStartAndEnd   ( const Vector2i& fieldLocation,
                                 int& xStart, int& yStart,
                                 int& xEnd,   int& yEnd )
{
    xStart = fieldLocation.x - areaVisible + 1;
    xEnd   = fieldLocation.x + areaVisible;

    yStart = fieldLocation.y - areaVisible + 1;
    yEnd = fieldLocation.y   + areaVisible;

    if ( xStart < 0 )
        xStart = 0;

    if ( yStart < 0 )
        yStart = 0;

    if ( xEnd > m_size.x)
        xEnd = m_size.x;

    if ( yEnd > m_size.y)
        yEnd = m_size.y;
}
