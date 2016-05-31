#ifndef MAP_H
#define MAP_H

#include "Maths/vector2.h"

#include <string>
#include <vector>

class Map
{
    friend class Map_Loader;

    Vector2i        m_location;
    Vector2i        m_size;
    std::string     m_currentArea;

    std::vector < char > m_blockTiles =
    {
        '#'
    };

    public:
        Map     ( const int x, const int y );

        void
        draw    ( const Vector2i& fieldLocation );

        char
        at      ( const int x, const int y) const;

        char
        at      ( const Vector2i& location ) const;

        const std::vector<char>&
        getBlockTiles () const;

    private:

};

#endif // MAP_H
