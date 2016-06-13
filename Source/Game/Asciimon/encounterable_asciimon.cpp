#include "encounterable_asciimon.h"

Encounterable_ASCIImon :: Encounterable_ASCIImon( const int id, const int weight )
:   m_id        ( id )
,   m_weight    ( weight)
{ }

int
Encounterable_ASCIImon :: getId () const
{
    return m_id;
}

int
Encounterable_ASCIImon :: getWeight () const
{
    return m_weight;
}
