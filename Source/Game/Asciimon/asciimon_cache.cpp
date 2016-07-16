#include "asciimon_cache.h"

#include "t_casts.h"
#include "game_funcs.h"
#include "console_funcs.h"

#include <iostream>

std::map<unsigned, Asciimon_Cache> mainAsciimonCache;


bool Asciimon_Cache :: idExists( unsigned id )
{
    return mainAsciimonCache.count ( id );
}

const Asciimon_Cache& Asciimon_Cache ::  getAsciimon  ( unsigned id )
{
    try
    {
        return mainAsciimonCache.at( id );
    }
    catch (std::out_of_range e)
    {
        throw std::runtime_error ( "Cannot find ID for ASCIImon " + Convert::toString( id ) );
    }
}

void Asciimon_Cache :: addAsciimonId (unsigned id, Asciimon_Cache& cache)
{
    mainAsciimonCache[ id ] = cache;
}

void Asciimon_Cache :: drawFront() const
{
    m_frontImage.draw();
}

void Asciimon_Cache :: drawBack() const
{
    m_backImage.draw();
}

const Image& Asciimon_Cache :: getFrontImage() const
{
    return m_frontImage;
}

const Image& Asciimon_Cache :: getBackImage() const
{
    return m_backImage;
}


const Asciimon_Cache::Base_Stats& Asciimon_Cache::getBaseStats() const
{
    return m_baseStats;
}

const std::string& Asciimon_Cache :: getName () const
{
    return m_name;
}

void Asciimon_Cache :: addLevelUpMove ( const Level_Up_Move& move )
{
    m_levelUpMoves.push_back( move );
}

const std::vector<Level_Up_Move>
Asciimon_Cache :: getLevelUpMoves () const
{
    return m_levelUpMoves;
}
