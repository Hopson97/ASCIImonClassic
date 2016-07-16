#ifndef ASCIIMON_DATA_H_INCLUDED
#define ASCIIMON_DATA_H_INCLUDED

#include "Asciimon/asciimon_stat.h"
#include "e_stat_names.h"
#include "asciimon_cache.h"

#include <map>


class Asciimon_Data
{
    friend class Asciimon_Loader;

    public:
        Asciimon_Data();

        void levelUp ( const Asciimon_Cache& cache );

        const std::map<Stat_Name, Asciimon_Stat>& getStats () const;

    private:
        std::map<Stat_Name, Asciimon_Stat> m_stats;
};


#endif // ASCIIMON_DATA_H_INCLUDED
