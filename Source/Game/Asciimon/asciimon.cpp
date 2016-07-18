#include "asciimon.h"

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <stdexcept>

#include "game_funcs.h"
#include "d_stat_names.h"
#include "move_loader.h"
#include "random_functions.h"
#include "console_funcs.h"
#include "d_stat_names.h"
#include "t_casts.h"

void Asciimon ::operator =( const Asciimon& evolvingInto )
{
    m_asciimonCache = evolvingInto.m_asciimonCache;
    m_stats = evolvingInto.m_stats;
}

const Asciimon_Data& Asciimon :: getStats () const
{
    return m_stats;
}

const Asciimon_Stat Asciimon :: getStat ( Stat_Name name ) const
{
    return m_stats.getStats().at( name );
}

void Asciimon :: setLevel( unsigned level)
{
    m_level.setLevel ( level );

    //Function is not not used here (Asciimon::checkForLvlUpMove) as this is a special case where it just randomly can replace moves
    for ( auto& move : m_asciimonCache->getLevelUpMoves() )
    {
        if ( move.level <= level )
        {
            addMove( move.name );
            if ( m_moves.size() > Asciimon_Move::MAX_MOVES )
            {
                m_moves.erase( m_moves.begin() + Random::integer( 0, Asciimon_Move::MAX_MOVES - 1 ) );
            }
        }
    }

    for ( unsigned i = 0 ; i < level ; i++ )
    {
        m_stats.levelUp( *m_asciimonCache );
    }
    if ( getMoves().size() < 1 )
    {
        std::cout << m_asciimonCache->getLevelUpMoves().size() << std::endl;
        throw std::runtime_error ( "No moved added to Asciimon " );
    }
}


const Level& Asciimon :: getLevel() const
{
    return m_level;
}


void Asciimon :: drawFront ( bool useTypeColours ) const
{
    if ( useTypeColours ) Console::setTextColour( getTypeColour() );
    m_asciimonCache->drawFront();
    Console::resetColours();
}


void Asciimon :: drawBack ( bool useTypeColours ) const
{
    if ( useTypeColours ) Console::setTextColour( getTypeColour() );
    m_asciimonCache->drawBack();
    Console::resetColours();
}


const Image& Asciimon :: getFrontImage() const
{
    return m_asciimonCache->getFrontImage();
}


const Image& Asciimon :: getBackImage() const
{
    return m_asciimonCache->getBackImage();
}


void Asciimon :: printStats () const
{
    std::cout << Stat_Name_S::Full::hitpoints;
    m_stats.getStats().at( Stat_Name::Hit_Points ).print();

    std::cout << Stat_Name_S::Full::attack;
    m_stats.getStats().at( Stat_Name::Attack ).print();

    std::cout << Stat_Name_S::Full::defence;
    m_stats.getStats().at( Stat_Name::Defence ).print();


    std::cout << Stat_Name_S::Full::spAttack;
    m_stats.getStats().at( Stat_Name::Special_Attack ).print();

    std::cout << Stat_Name_S::Full::spDefence;
    m_stats.getStats().at( Stat_Name::Special_Defence ).print();


    std::cout << Stat_Name_S::Full::speed;
    m_stats.getStats().at( Stat_Name::Speed ).print();
}

const std::string& Asciimon :: getName () const
{
    return m_asciimonCache->getName();
}

void Asciimon :: addMove ( const std::string& name )
{
    Move_Loader loader;
    Asciimon_Move realMove;
    loader.load( &realMove, name );
    m_moves.push_back( realMove );
}

const std::vector<Asciimon_Move>&
Asciimon :: getMoves () const
{
    return m_moves;
}

void Asciimon::printHealth() const
{
    std::cout << Stat_Name_S::Full::hitpoints << " ";
    m_stats.getStats().at( Stat_Name::Hit_Points ).print();
}

void Asciimon::printLevel() const
{
    std::cout << "Level: " << m_level.getLevel() << std::endl;
}

double Asciimon :: getInitialDamage ( const Asciimon& attacker )
{
    double level       = attacker.getLevel().getLevel();
    double attack      = attacker.getStat( Stat_Name::Attack ).getCurrValue();
    double base        = attacker.m_asciimonCache->getBaseStats().attack;

    double defence     = getStat( Stat_Name::Defence ).getCurrValue();

    double dmg1 = (2 * level + 10) / 250;
    double dmg2 = (attack / defence);
    double dmg3 = base + 2;

    Game::printToLog( "dmg1 : " + Convert::toString( dmg1 ) );
    Game::printToLog( "dmg2 : " + Convert::toString( dmg2 ) );
    Game::printToLog( "dmg3 : " + Convert::toString( dmg3 ) );

    double dmg = dmg1 * dmg2 * dmg3;

    return dmg;
}

double Asciimon :: getModifier ( const Asciimon& attacker, const Asciimon_Move& move )
{
    //"same type attack bonus"
    double stab =  ( move.getInfo().m_type == attacker.m_asciimonCache->getType() )? 1.5 : 1;
    //TYPE
    double critical = ( Random::integer(1, 10 ) == 1 ) ? 2 : 1;
    //items?
    double rnd = Random::decimal( 0.85, 1.15 );

    Game::printToLog( "stab : " +        Convert::toString( stab ) );
    Game::printToLog( "critical : " +    Convert::toString( critical ) );
    Game::printToLog( "rnd : " +         Convert::toString( rnd ) );

    return stab * critical * rnd;

}

bool Asciimon :: hit ( const Asciimon& attacker, const Asciimon_Move& move )
{
    double damage = getInitialDamage( attacker );

    double mod = getModifier( attacker, move );

    double finalDamage = ceil( damage * mod );

    Game::printToLog( "Damage : " +  Convert::toString( finalDamage ) );
    Game::printToLog( "Mod : " +     Convert::toString( mod ) );
    Game::printToLog( "Initial : " + Convert::toString( damage ) );

    if ( damage <= 0 )
    {
        damage = 0;
        return false;
    }

    finalDamage *= 1.5;

    m_stats.deductStat( Stat_Name::Hit_Points, finalDamage );

    return true;
}


void Asciimon :: addExp ( unsigned amount )
{
   m_level.giveExp( amount );
}

bool Asciimon :: canLevelUp  ()
{
    bool leveled = false;
    while ( m_level.canLevelUp() )
    {
        auto prevLevel = m_level.getLevel();
        m_level.levelUp();
        Console::clear();
        std::cout << "Level up! " << prevLevel << " -> " << m_level.getLevel() << std::endl;
        Game::pressEnterToContinue();

        auto prevStats = m_stats.getStats();
        m_stats.levelUp( *m_asciimonCache );

        Console::newLine();

        printLevelUp( prevStats );
        checkForLvlUpMove( true );
        leveled = true;
    }
    return leveled;
}

bool Asciimon :: canEvolve ()
{
    if ( m_asciimonCache->getEvolution().level == 0 ) return false;
    return m_level.getLevel() >= m_asciimonCache->getEvolution().level;
}

unsigned Asciimon :: getEvolveId ()
{
    return m_asciimonCache->getEvolution().intoId;
}

void Asciimon :: printLevelUp (  std::map< Stat_Name, Asciimon_Stat >& prevStats ) const
{
        auto nowStats = m_stats.getStats();

        auto printStat = [&]( Stat_Name stat, const std::string& name_s, int tabs )
        {
            std::cout << name_s;
            for ( int i = 0 ; i < tabs ; i++ ) std::cout << "\t";
            prevStats.at ( stat ).printVal();
            std::cout << " -> ";
            nowStats.at ( stat ).printVal();
            Console::newLine();
        };

        printStat ( Stat_Name::Hit_Points,      Stat_Name_S::Full::hitpoints,   1   );
        printStat ( Stat_Name::Attack,          Stat_Name_S::Full::attack,      2   );
        printStat ( Stat_Name::Special_Attack,  Stat_Name_S::Full::spAttack,    1   );
        printStat ( Stat_Name::Defence,         Stat_Name_S::Full::defence,     2   );
        printStat ( Stat_Name::Special_Defence, Stat_Name_S::Full::spDefence,   1   );
        printStat ( Stat_Name::Speed,           Stat_Name_S::Full::speed,       2   );

        Game::pressEnterToContinue();
        Console::clear();
}


bool Asciimon :: isFainted ()
{
    return ( getStat( Stat_Name::Hit_Points).getCurrValue() <= 0 );
}

unsigned Asciimon :: getFaintExp ()
{
    return m_asciimonCache->getBaseIncreases().exp * m_level.getLevel();
}

Asciimon_Move& Asciimon :: getMove ( int index )
{
    return m_moves.at( index );
}

void Asciimon :: checkForLvlUpMove  ( bool announce )
{
    for ( auto& move : m_asciimonCache->getLevelUpMoves() )
    {

        bool alreadyHasMove = false;

        for ( auto& gotMoves : m_moves )
            if ( gotMoves.getInfo().name == move.name ) alreadyHasMove = true;

        if ( alreadyHasMove ) continue;

        if ( move.level <= getLevel().getLevel() )
        {
            addMove( move.name );
            if ( announce )
            {
                std::cout << getName() << " has learned " << move.name << "!" << std::endl;
                Game::pressEnterToContinue();
            }
        }
    }
}


Console::Foreground_Colour Asciimon::getTypeColour() const
{
    return Asciimon_Type_Colours::convert.at( m_asciimonCache->getType() );
}

void Asciimon::fullRestore()
{
    m_stats.fullRestore();
}

