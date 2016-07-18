#ifndef GENERAL_FUNCS_H_INCLUDED
#define GENERAL_FUNCS_H_INCLUDED

#include <string>
#include <fstream>
#include <iostream>
#include <functional>

#include "game_funcs.h"

namespace General
{
    bool lineContains       ( const std::string& line, const std::string checkFor );
    void openFile           ( const std::string& fileName, std::ifstream& inFile );

    bool isStringNumrical   ( const std::string& str );

    unsigned getInput       ( int min, int max,
                             std::function<void(void)> printOptions, std::function<void(void)> invalidInput);
}


#endif // GENERAL_FUNCS_H_INCLUDED
