#ifndef ASCIIMON_EVOLVER_H
#define ASCIIMON_EVOLVER_H

#include "asciimon.h"

class Asciimon_Evolver
{
    public:
        Asciimon_Evolver( Asciimon& asciimon, unsigned id );

        void evolve     ();

    private:
        Asciimon getEvolvingInto ();

        Asciimon&   m_asciimon;
        unsigned    m_evolveIntoId;
};

#endif // ASCIIMON_EVOLVER_H
