#include "random_functions.h"

#include <ctime>
#include <cstdlib>

namespace Random
{

int
integer ( const int low, const int high)
{
    return rand() % (high - low + 1) + low;
}

}
