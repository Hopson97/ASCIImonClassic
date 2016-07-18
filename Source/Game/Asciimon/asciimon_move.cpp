#include "asciimon_move.h"

#include <iostream>

void Asciimon_Move :: use()
{
    m_info->playSound();
    m_movesLeft--;
}

void Asciimon_Move :: printStatus() const
{
    std::cout << "PP: " << m_movesLeft << "/" << m_info->getInfo().maxPowerPoints;
}



void Asciimon_Move :: reset ()
{
    m_movesLeft = m_info->getInfo().maxPowerPoints;
}

const Asciimon_Move_Cache::Info&
Asciimon_Move :: getInfo () const
{
    return m_info->getInfo();
}
