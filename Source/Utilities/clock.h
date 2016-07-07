#ifndef CLOCK_H
#define CLOCK_H

#include <chrono>


class Clock
{
    using Time_Point = std::chrono::steady_clock::time_point;

    Time_Point m_currentTime;

    public:
        Clock                       ();

        double getCurrentTime       () const;

        double restart              ();

    private:
        Time_Point getChronoTime    () const;

        double timeToSeconds        ( const Time_Point& otherTime ) const;
};

#endif // CLOCK_H
