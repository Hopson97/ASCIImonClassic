#include "player.h"

#include <iostream>
#include "asciimon.h"
#include "asciimon_loader.h"

Player :: Player()
{
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

void Player :: give ( const Asciimon& asciimon )
{
    m_asciimon.insert( m_asciimon.begin(), asciimon );
}

void Player :: healAll ()
{
    for ( Asciimon& asciimon : m_asciimon )
    {
        asciimon.fullRestore();
    }
}

const Vector2i& Player :: getDirection ()
{
    return m_fieldData.direction;
}

















