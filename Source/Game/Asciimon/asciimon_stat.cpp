#include "asciimon_stat.h"

#include <iostream>








Asciimon_Stat :: Asciimon_Stat ( unsigned level )
{
    m_currentValue = level;
    m_maxValue = level;
}

void Asciimon_Stat :: levelUp ( double levelUpMultiplier )
{
    m_maxValue *= levelUpMultiplier;
}

void Asciimon_Stat :: print ()
{
    std::cout << m_currentValue << " / " << m_maxValue << std::endl;
}
