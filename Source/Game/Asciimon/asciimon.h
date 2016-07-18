#ifndef ASCIIMON_H
#define ASCIIMON_H

#include <vector>

#include "asciimon_data.h"
#include "level.h"
#include "asciimon_move.h"

#include "asciimon_cache.h"

class Asciimon
{
    friend class Asciimon_Loader;
    friend class Asciimon_Evolver;

    public:
        Asciimon() = default;

        void operator =( const Asciimon& evolvingInto );

        const Asciimon_Data& getStats () const;

        const Asciimon_Stat getStat   ( Stat_Name name ) const;

        void drawFront  ( bool useTypeColours = true ) const;
        void drawBack   ( bool useTypeColours = true ) const;
        const Image& getFrontImage  () const;
        const Image& getBackImage   () const;

        void printStats     () const;
        void printHealth    () const;
        void printLevel     () const;

        void setLevel   ( unsigned level );
        const Level& getLevel       () const;

        const std::string& getName  () const;

        const std::vector<Asciimon_Move>& getMoves () const;

        bool hit    ( const Asciimon& attacker, const Asciimon_Move& move );

        void addExp             ( unsigned amount );
        bool canLevelUp         ();
        bool canEvolve          ();
        unsigned getEvolveId    ();

        bool isFainted          ();
        unsigned getFaintExp    ();

        Asciimon_Move& getMove ( int index );

        Console::Foreground_Colour  getTypeColour () const;

        void fullRestore ();

    private:
        double getInitialDamage ( const Asciimon& attacker );
        double getModifier      ( const Asciimon& attacker, const Asciimon_Move& move );

        void addMove ( const std::string& name );

        void printLevelUp       ( std::map< Stat_Name, Asciimon_Stat >& prevStats ) const;

        void checkForLvlUpMove  ( bool announce = false );

        Asciimon_Data   m_stats;
        Level           m_level;

        std::string     m_name = " ";

        const Asciimon_Cache* m_asciimonCache = nullptr;

        std::vector<Asciimon_Move> m_moves;
};

#endif // ASCIIMON_H
