#include "encounterable_asciimon.h"

Encounterable_ASCIImon :: Encounterable_ASCIImon( const unsigned id, const unsigned weight,
                                                  const unsigned lowerLvlBound, const unsigned upperLvlBound )
:   m_id        ( id )
,   m_weight    ( weight)
,   m_lowerLevelRange   ( lowerLvlBound )
,   m_upperLevelRange   ( upperLvlBound )
{ }

unsigned Encounterable_ASCIImon :: getId () const
{
    return m_id;
}

unsigned Encounterable_ASCIImon :: getWeight () const
{
    return m_weight;
}

unsigned Encounterable_ASCIImon :: getLowLevel() const
{
    return m_lowerLevelRange;
}

unsigned Encounterable_ASCIImon :: getHighLevel() const
{
    return m_upperLevelRange;
}

