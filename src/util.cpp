#include "util.h"
#include <math.h>

namespace rayTracer
{
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
