#include "move_loader.h"

#include <string>

#include "e_asciimon_types.h"

const std::string Move_Loader :: getFileName () const
{
    return "Data/Moves/" + m_name + ".move";
}

void Move_Loader :: load ( Asciimon_Move* move, const std::string& name )
{
    m_p_move = move;
    m_name = name;
    m_cache = Asciimon_Move_Cache(); //reset

    if ( !Asciimon_Move_Cache::moveExists( name ) )
    {
        m_cache.m_info.name = name;

        bindKeywords();

        readFile( "Move file (.move) " );

        Asciimon_Move_Cache::addMove( name, m_cache );
    }

    m_p_move->m_info = &Asciimon_Move_Cache::getMove( name );
    m_p_move->reset();
}

void Move_Loader :: getType ()
{
    int n;

    Loader_Base::readNumber( n );
    m_cache.m_info.m_type = static_cast<Asciimon_Type>( n );
}

void Move_Loader :: bindKeywords()
{
    addKeyword( m_cache.m_info.power,           "POWER" );
    addKeyword( m_cache.m_info.maxPowerPoints,  "PP"    );
    addKeyword( m_cache.m_info.isSpecial,       "SP"    );

    addKeyword( std::bind ( &Move_Loader::getType, this), "TYPE" );
}
