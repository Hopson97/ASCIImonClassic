#ifndef ASCIIMON_CACHE_H
#define ASCIIMON_CACHE_H

#include "Image.h"
#include "e_asciimon_types.h"
#include "asciimon_move.h"

#include <map>
#include <vector>


//The cache just hold general information about a Asciimon that never changes so that they need not be loaded multiple times

class Asciimon_Cache
{
    friend class Asciimon_Loader;

    struct Base_Stats
    {
        unsigned attack;
        unsigned spAttack;

        unsigned defence;
        unsigned spDefence;

        unsigned hitpoints;
        unsigned speed;
    } m_baseStats;

    struct Base_Increases
    {
        unsigned attack;
        unsigned spAttack;

        unsigned defence;
        unsigned spDefence;

        unsigned hitpoints;
        unsigned speed;
    } m_baseIncreases;

    public:
        static bool idExists                ( unsigned id );
        static void addAsciimonId           ( unsigned id, Asciimon_Cache& cache );
        static const Asciimon_Cache& getAsciimon  ( unsigned id );

        void drawFront  () const;
        void drawBack   () const;

        const Image& getFrontImage  () const;
        const Image& getBackImage   () const;

        const Base_Increases& getBaseIncreases () const;

        const Base_Stats&  getBaseStats () const;
        const std::string& getName      () const;

        void addLevelUpMove ( const Level_Up_Move& move );

        const std::vector<Level_Up_Move> getLevelUpMoves () const;

    private:
        Image m_frontImage;
        Image m_backImage;

        std::string m_name = " ";
        Asciimon_Type m_type;

        std::vector<Level_Up_Move> m_levelUpMoves;
};

#endif // ASCIIMON_CACHE_H
