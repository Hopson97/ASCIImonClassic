#ifndef ASCIIMON_STAT_H_INCLUDED
#define ASCIIMON_STAT_H_INCLUDED

#include <string>

class Asciimon_Stat
{
    public:
        Asciimon_Stat () = default;
        Asciimon_Stat ( unsigned level );

        void levelUp    ( double levelUpMultiplier );

        void print      ();

    private:
        unsigned m_maxValue;
        unsigned m_currentValue;
};

#endif // ASCIIMON_STAT_H_INCLUDED
