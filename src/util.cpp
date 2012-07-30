#include "util.h"

#include <math.h>
#include "vector.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
void Clamp( float& io_value, float _min, float _max )
{
	if( io_value > _max )
		io_value = _max;
	else if( io_value < _min )
		io_value = _min;
}
//------------------------------------------------------------------------------
float min( const float& _a, const float& _b, const float& _c )
{
	return std::min( _a, std::min( _b, _c) );
}
//------------------------------------------------------------------------------
float max( const float& _a, const float& _b, const float& _c )
{
	return std::max( _a, std::max( _b, _c) );
}
//------------------------------------------------------------------------------
bool RealCompare( const float& _a, const float& _b, const float& _epsilon)
{
	if ( fabs( _a - _b ) < _epsilon )
		return true;
	else return false;
}
//------------------------------------------------------------------------------
void SampleSquare( std::vector<Vector2D>& o_samples, uint32_t _num )
{
	float size = 1.0/(float)_num;

	for( uint32_t i=0; i< _num ; ++i )
	{
		for( uint32_t j=0; j< _num ; ++j )
		{
			float x = i * size;
			float y = j * size;
			o_samples.push_back( Vector2D( x + rand()/(float)RAND_MAX*size,  y + rand()/(float)RAND_MAX*size) );
		}
	}
}
//------------------------------------------------------------------------------
void SampleHemisphere ( std::vector<Vector>& o_samples, uint32_t _num, uint32_t _exp )
{
	//generate planesamples within 0 and 1
	std::vector<Vector2D> squareSamples;
	SampleSquare( squareSamples, _num );
	uint32_t sampleSize = squareSamples.size();
	for( uint32_t i=0; i< sampleSize; ++i )
	{
		float phi = 2.0f * PI * squareSamples[i].u();
		float theta = acos( pow( (1-squareSamples[i].v() ), 1.0/(_exp + 1) ) );
		float sinTheta = sin (theta);
		float cosTheta = cos (theta);
		float sinPhi = sin (phi);
		float cosPhi = cos (phi);
		Vector p= Vector(1,0,0,0) * sinTheta * cosPhi + Vector(0,0,1,0)* sinTheta * sinPhi + Vector(0,1,0,0) * cosTheta ;
		o_samples.push_back(p);
	}
}
}//end of namespace
