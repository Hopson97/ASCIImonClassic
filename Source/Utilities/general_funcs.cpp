#include "general_funcs.h"

#include <stdexcept>
#include <cstdlib>
#include <keyboard.h>

namespace General
{

bool lineContains   ( const std::string& line, const std::string checkFor )
{
    return line.find ( checkFor ) != std::string::npos;
}


void openFile ( const std::string& fileName, std::ifstream& inFile )
{
    inFile.open ( fileName );
    if ( !inFile.is_open() ) throw std::runtime_error ( "Could not open file: " + fileName );
}

bool isStringNumrical ( const std::string& str )
{
    for ( auto& c : str )
    {
        if ( !std::isdigit( c ) ) return false;;
    }

    return true;
}

unsigned getInput ( int min, int max,
                    std::function<void(void)> printOptions, std::function<void(void)> invalidInput)
{
    int input;
    while ( true )
    {
        input = (int)Keyboard::waitForKey();

        if ( !std::isdigit( input ) )
        {
            invalidInput();
            printOptions();
            continue;
        }

        input -= 48;

        if ( !(input >= min && input <= max ) )
        {
            invalidInput();
            printOptions();
            continue;
        }
        break;
    }
    return input;
}









}
