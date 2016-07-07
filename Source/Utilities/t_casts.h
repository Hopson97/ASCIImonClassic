#ifndef T_CASTS_H_INCLUDED
#define T_CASTS_H_INCLUDED

#include <sstream>

namespace Convert
{
    template<typename T>
    short unsigned shortUnsigned ( const T num )
    {
        return static_cast < short unsigned > ( num );
    }

    template<typename T>
    std::string toString ( const T num )
    {
        std::ostringstream stream;
        stream << num;
        return stream.str();
    }

    template<typename T>
    T toNumber ( const std::string& str )
    {
        int num = 0;
        std::istringstream stream ( str );
        stream >> num;
        return num;
    }

}

#endif // T_CASTS_H_INCLUDED
