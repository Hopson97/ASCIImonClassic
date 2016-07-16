#include "asciimon_move.h"

void Asciimon_Move :: reset ()
{
    m_movesLeft = m_info->getInfo().maxPowerPoints;
}
