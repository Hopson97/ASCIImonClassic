#include "general_funcs.h"

#include <stdexcept>
#include <cstdlib>

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

}
