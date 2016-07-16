#include "asciimon.h"

#include <iostream>

#include "game_funcs.h"
#include "d_stat_names.h"
#include "move_loader.h"
#include "random_functions.h"

void Asciimon :: setLevel( unsigned level)
{
    m_level.setLevel ( level );

    for ( auto& move : m_asciimonCache->getLevelUpMoves() )
    {
        if ( move.level <= level )
        {
            addMove( move.name );
            if ( m_moves.size() > Asciimon_Move::MAX_MOVES )
            {
                m_moves.erase( m_moves.begin() + Random::integer( 0, Asciimon_Move::MAX_MOVES - 1 ) );
            }
        }
    }
}


const unsigned Asciimon :: getLevel() const
{
    return m_level.getLevel();
}


void Asciimon :: drawFront () const
{
    m_asciimonCache->drawFront();
}


void Asciimon :: drawBack () const
{
    m_asciimonCache->drawBack();
}


const Image& Asciimon :: getFrontImage() const
{
    return m_asciimonCache->getFrontImage();
}


const Image& Asciimon :: getBackImage() const
{
    return m_asciimonCache->getBackImage();
}


void Asciimon :: printStats ()
{
    std::cout << Stat_Name_S::Full::hitpoints;
    m_stats.stats.at( Stat_Name::Hit_Points ).print();

    std::cout << Stat_Name_S::Full::attack;
    m_stats.stats.at( Stat_Name::Attack ).print();

    std::cout << Stat_Name_S::Full::defence;
    m_stats.stats.at( Stat_Name::Defence ).print();


    std::cout << Stat_Name_S::Full::spAttack;
    m_stats.stats.at( Stat_Name::Special_Attack ).print();

    std::cout << Stat_Name_S::Full::spDefence;
    m_stats.stats.at( Stat_Name::Special_Defence ).print();


    std::cout << Stat_Name_S::Full::speed;
    m_stats.stats.at( Stat_Name::Speed ).print();
}

const std::string& Asciimon :: getName () const
{
    return m_asciimonCache->getName();
}

void Asciimon :: addMove ( const std::string& name )
{
    Move_Loader loader;
    Asciimon_Move realMove;
    loader.load( &realMove, name );
    m_moves.push_back( realMove );
}
