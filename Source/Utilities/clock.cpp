#include "clock.h"

#include <cmath>

typedef std::chrono::steady_clock::time_point Time_Point;

Clock :: Clock()
{
    m_currentTime = getChronoTime();
}

double Clock :: getCurrentTime () const
{
    double time = timeToSeconds( getChronoTime() );
    return time;
}

double Clock :: restart ()
{
    double time = timeToSeconds( getChronoTime() );
    m_currentTime = getChronoTime();
    return time;
}

Time_Point Clock :: getChronoTime () const
{
    return std::chrono::steady_clock::now();
}

//The verbosity of std::chrono is just awful...
double Clock :: timeToSeconds ( const Time_Point& otherTime ) const
{
    return std::chrono::duration_cast
           < std::chrono::microseconds> ( otherTime - m_currentTime )
           .count() * pow (10, -6);
}
