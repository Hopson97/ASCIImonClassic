#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>
#include <map>

#include "Maths/vector2.h"
#include "portal.h"

class Map
{
    friend class Map_Loader;

    Vector2i            m_location;
    Vector2i            m_size;
    std::string         m_currentArea;
    std::vector<Portal> m_portals;

    //These maps are defined in "d_tiles.h"

    public:
        Map                     ( const int x, const int y );

        void
        draw                    ( const Vector2i& fieldLocation );

        const Vector2i&
        getLocation             () const;

        void
        setLocation             ( const Vector2i& location );

        char
        at                      ( const int x, const int y) const;

        char
        at                      ( const Vector2i& location ) const;

        void
        moveMap                 ( const Vector2i& amount );

        const Vector2i&
        getSize                 () const;

        const Portal&
        getPortalAt             ( const Vector2i& location ) const;

    private:
        void
        setTileColour           ( const char tile );

        void
        getMapDrawStartAndEnd   ( const Vector2i& fieldLocation,
                                  int& xStart, int& yStart,
                                  int& xEnd,   int& yEnd );

};

#endif // MAP_H
