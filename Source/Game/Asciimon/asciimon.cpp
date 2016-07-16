#include "asciimon.h"

#include <iostream>

#include "game_funcs.h"
#include "d_stat_names.h"

void Asciimon :: setLevel( unsigned level)
{
    m_level.setLevel ( level );
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
