#include "game_funcs.h"

#include "../Utilities/windows_funcs.h"
#include "../Utilities/console_funcs.h"
#include "../Utilities/clock.h"
#include "t_casts.h"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <ctime>

namespace Game
{

void shortPause ( double seconds )
{
    Clock clock;
    while ( clock.getCurrentTime() < seconds );
}

void pressEnterToContinue ()
{
    Console::setTextColour( Console::Foreground_Colour::GRAY );
    Console::newLine();

    std::cout << "Press enter to continue...";
    std::cin.sync();
    std::cin.get();
    Console::resetColours();

    Console::newLine();
}

void printLine ( const std::string& line )
{
    std::cout << line << std::endl;
}

void message ( const std::string& text )
{
    std::cout << text << std::endl;
    pressEnterToContinue();
    printToLog( text );
}

std::ofstream outLog;

static std::string getTime ()
{
    time_t t = time(0);
    tm* now = localtime( &t );

    auto year   = now->tm_year + 1900;
    auto month  = now->tm_mon + 1;
    auto day    = now->tm_mday;

    std::string date = Convert::toString( day ) + "-" + Convert::toString( month ) + "-" + Convert::toString( year );

    auto h = now->tm_hour;
    auto m = now->tm_min;
    auto s = now->tm_sec;

    std::string timeString = Convert::toString( h ) + "-" + Convert::toString( m ) + "-" + Convert::toString( s );

    return date + " " + timeString;


}

void openLog()
{
    std::string path = "Log/Log ";
    std::string file = path + getTime();
    outLog.open( file + ".txt" );
}

void printToLog ( const std::string& line )
{
    outLog << line << std::endl;
}

}
