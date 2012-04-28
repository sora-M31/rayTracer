#include "util.h"
#include <math.h>

namespace rayTracer
{
//------------------------------------------------------------------------------
//Method from http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
void Tokenize ( const std::string& _str,
                std::list<std::string>& o_tokens,
                const std::string& _delimiters )
{
    std::string::size_type lastPos = _str.find_first_not_of ( _delimiters, 0 );
    std::string::size_type pos = _str.find_first_of ( _delimiters, lastPos );

    while ( pos != std::string::npos || lastPos != std::string::npos )
    {
        o_tokens.push_back ( _str.substr ( lastPos, pos-lastPos ) );
        lastPos = _str.find_first_not_of ( _delimiters,pos );
        pos = _str.find_first_of ( _delimiters, lastPos );
    }
}
//------------------------------------------------------------------------------
bool RealEqual ( const float _x, const float _y )
{
    if ( fabs ( _x - _y) < EPSILON )
        return true;
    return false;
}
}//end of namespace
