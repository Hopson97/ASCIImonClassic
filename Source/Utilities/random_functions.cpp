#include "random_functions.h"

#include <ctime>
#include <cstdlib>

namespace Random
{

int integer ( int low, int high )
{
    return rand() % (high - low + 1) + low;
}

double decimal ( double low, double high )
{
    low *= 100;
    high *= 100;

    double newNum = integer( low, high );

    return newNum / 100;
}

}
