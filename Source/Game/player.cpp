#include "player.h"

#include <iostream>
#include "asciimon.h"
#include "asciimon_loader.h"

Player :: Player()
{
    Asciimon_Loader loader;
    Asciimon a;

    loader.load( &a, 1 );
    m_asciimon.push_back( a );
}

const Vector2i& Player :: getFieldLocation() const
{
    return m_fieldData.location;
}

void Player :: moveInField ( const Vector2i& amount )
{
    m_fieldData.location += amount;
    m_fieldData.direction = amount;

    if ( m_fieldData.direction.x > 1  ) m_fieldData.direction.x =  1;
    if ( m_fieldData.direction.x < -1 ) m_fieldData.direction.x = -1;
    if ( m_fieldData.direction.y > 1  ) m_fieldData.direction.y =  1;
    if ( m_fieldData.direction.y < -1 ) m_fieldData.direction.y = -1;
}

void Player :: setFieldPosition ( const Vector2i& location )
{
    m_fieldData.location = location;
}

Asciimon& Player :: getFrontAsciimon ()
{
    return m_asciimon.at( 0 );
}

void Player :: setName ( const std::string& name )
{
    m_name = name;
}
