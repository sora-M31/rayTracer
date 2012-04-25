#include "util.h"
#include <math.h>

namespace rayTracer
{
//------------------------------------------------------------------------------
//Method from http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html
void Tokenize ( const std::string& str,
           std::list<std::string>& tokens,
           const std::string& delimiters)
{
    std::string::size_type lastPos = str.find_first_not_of( delimiters, 0);
    std::string::size_type pos = str.find_first_of(delimiters, lastPos);

    while( pos != std::string::npos || lastPos != std::string::npos )
    {
        tokens.push_back(str.substr(lastPos, pos-lastPos) );
        lastPos = str.find_first_not_of(delimiters,pos);
        pos = str.find_first_of( delimiters, lastPos);
    }
}
//------------------------------------------------------------------------------
bool RealEqual(const float _x, const float _y)
{
    if( fabs(_x - _y) < EPSILON )
        return true;
    return false;
}
}//end of namespace
