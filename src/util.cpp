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
void Sampling ( const Vector& _centre, float _width, float _height, float _gridNumberU, float _gridNumberV, const Vector& _u, const Vector& _v, std::list<Vector>& o_samples)
{
	Vector leftBottom = _centre - _u * _width / 2.0f - _v * _height / 2.0f;
	//size of each grid
	float unitU = _width / _gridNumberU;
	float unitV = _height / _gridNumberV;

	for( uint32_t row = 0; row < _gridNumberU; ++row )
		for( uint32_t column = 0; column < _gridNumberV; ++column )
		{
			//random()%100/100.0f - 0.5 is between -0.5 to 0.5
			o_samples.push_back( leftBottom
								 + _u * unitU * ( row + random()%50/50.0f - 0.5 )
								 + _v * unitV * ( column + random()%50/50.0f - 0.5 ) ) ;
		}
}
}//end of namespace
