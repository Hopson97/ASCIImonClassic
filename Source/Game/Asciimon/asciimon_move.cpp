#include "asciimon_move.h"

void Asciimon_Move :: reset ()
{
    m_movesLeft = m_info->getInfo().maxPowerPoints;
}

const Asciimon_Move_Cache::Info&
Asciimon_Move :: getInfo () const
{
    return m_info->getInfo();
}
