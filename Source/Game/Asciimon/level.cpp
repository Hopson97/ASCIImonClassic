#include "level.h"

void Level :: giveExp ( unsigned exp )
{
    m_currentExp += exp;
    m_totalExp += exp;
}

void Level :: checkForLevelUp ()
{
    if ( canLevelUp() )
    {
        levelUp();
    }
}

bool Level :: canLevelUp ()
{
    return m_currentExp >= m_expForNextLevel;
}

void Level :: levelUp()
{
    m_level++;

    m_currentExp = getExpOverflow();
    m_expForNextLevel *= expIncrease;

}

unsigned Level::getExpOverflow()
{
     unsigned leftOverExp = m_currentExp - m_expForNextLevel;
     return (leftOverExp > 0) ? leftOverExp : 0;
}



void Level :: setLevel ( unsigned level )
{
    while ( m_level <= level )
    {
        giveExp( 1 );
        checkForLevelUp();
        if ( m_level >= level ) break;
    }
}



unsigned Level :: getLevel() const
{
    return m_level;
}

unsigned Level :: getCurrentExp() const
{
    return m_currentExp;
}

unsigned Level :: getExpForNextLevel() const
{
    return m_expForNextLevel;
}

unsigned Level :: getTotalExp() const
{
    return m_totalExp;
}
