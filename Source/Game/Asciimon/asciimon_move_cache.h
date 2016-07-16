#ifndef ASCIIMON_MOVE_CACHE_H
#define ASCIIMON_MOVE_CACHE_H

#include <string>

#include "e_asciimon_types.h"

class Asciimon_Move_Cache
{
    friend class Move_Loader;

    public:
        struct Info
        {
            std::string name;
            unsigned    power;
            unsigned    maxPowerPoints;
            unsigned    isSpecial;

            Asciimon_Type   m_type;
        };

        static bool moveExists              ( const std::string& name );
        static void addMove                 ( const std::string& name, const Asciimon_Move_Cache& cache );
        static Asciimon_Move_Cache& getMove ( const std::string& name );

        const Info& getInfo () const;

    private:
        Info m_info;
};

#endif // ASCIIMON_MOVE_CACHE_H
