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
    m_currentValue += baseIncrease * levelUpMultiplier;

    if ( m_currentValue > m_maxValue ) m_currentValue = m_maxValue;
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

void Asciimon_Stat :: deduct ( unsigned amount )
{
    if ( (int)m_currentValue - (int)amount < 0 )
    {
        m_currentValue = 0;
        return;
    }
    m_currentValue -= amount;
}

void Asciimon_Stat :: reset ()
{
    m_currentValue = m_maxValue;
}

void Asciimon_Stat :: printVal ()
{
    std::cout << m_maxValue;
}
