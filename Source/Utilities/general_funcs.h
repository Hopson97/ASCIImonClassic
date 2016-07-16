#ifndef GENERAL_FUNCS_H_INCLUDED
#define GENERAL_FUNCS_H_INCLUDED

#include <string>
#include <fstream>

namespace General
{
    bool lineContains   ( const std::string& line, const std::string checkFor );
    void openFile       ( const std::string& fileName, std::ifstream& inFile );
}


#endif // GENERAL_FUNCS_H_INCLUDED
