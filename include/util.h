#ifndef _UTIL_H_
#define _UTIL_H_

#include <list>
#include <string>

namespace rayTracer
{
#define EPSILON 0.001
void Tokenize ( const std::string& _str, std::list<std::string>& o_tokens,const std::string& _delimiters) ;
bool RealEqual(const float _x, const float _y);
}
#endif
