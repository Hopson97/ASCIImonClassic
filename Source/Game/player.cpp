#include "player.h"

Player :: Player()
{

}

const Vector2i&
Player :: getFieldLocation() const
{
    return m_fieldLocation;
}

void
Player :: moveInField ( const Vector2i& amount )
{
    m_fieldLocation.x += amount.x;
    m_fieldLocation.y += amount.y;
}
