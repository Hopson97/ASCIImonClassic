#include "portal.h"

Portal :: Portal ( const Vector2i& location )
:   m_location ( location )
{

}

void Portal :: setUp ( const Vector2i& goesTo, const Vector2i& playerStands )
{
    m_goesTo        = goesTo;
    m_playerStands  = playerStands;
}


const Vector2i& Portal :: getGoesTo () const
{
    return m_goesTo;
}

const Vector2i& Portal :: getPlayerStands () const
{
    return m_playerStands;
}

const Vector2i& Portal :: getLocation () const
{
    return m_location;
}
