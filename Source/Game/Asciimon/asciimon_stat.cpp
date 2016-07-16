#include "asciimon_stat.h"

#include <iostream>


Asciimon_Stat :: Asciimon_Stat ( unsigned level )
{
    m_currentValue = level;
    m_maxValue = level;
}

void Asciimon_Stat :: levelUp ( double levelUpMultiplier, unsigned baseIncrease )
{
    m_maxValue += baseIncrease * levelUpMultiplier;
}

void Asciimon_Stat :: print () const
{
    std::cout << m_currentValue << " / " << m_maxValue << std::endl;
}

unsigned Asciimon_Stat :: getMaxValue () const
{
    return m_maxValue;
}

unsigned Asciimon_Stat :: getCurrValue () const
{
    return m_currentValue;
}
