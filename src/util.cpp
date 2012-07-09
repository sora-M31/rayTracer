#include "util.h"

#include <math.h>
#include "vector.h"

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
	return ( _a<_b ) ? ( (_a<_c )? _a : _c ) : ( ( _b<_c )? _b : _c );
}
//------------------------------------------------------------------------------
float max( const float& _a, const float& _b, const float& _c )
{
	return ( _a>_b ) ? ( (_a>_c )? _a : _c ) : ( ( _b>_c )? _b : _c );
}
//------------------------------------------------------------------------------
bool RealCompare( const float& _a, const float& _b, const float& _epsilon)
{
	if ( fabs( _a - _b ) < _epsilon )
		return true;
	else return false;
}
//------------------------------------------------------------------------------
void SampleSquare( std::vector<Vector2D>& o_samples)
{
	uint32_t grid = 15;
	float size = 1.0/(float)grid;

	for( uint32_t i=0; i< grid ; ++i )
	{
		for( uint32_t j=0; j< grid ; ++j )
		{
			float x = i * size;
			float y = j * size;
			o_samples.push_back( Vector2D( x + rand()/(float)RAND_MAX*size,  y + rand()/(float)RAND_MAX*size) );
		}
	}
}
//------------------------------------------------------------------------------
void SampleHemisphere ( std::vector<Vector>& o_samples)
{
	//generate planesamples within 0 and 1
	std::vector<Vector2D> squareSamples;
	SampleSquare( squareSamples );
	uint32_t sampleSize = squareSamples.size();
	uint32_t e = 10;
	float PI = 3.1415;
	for( uint32_t i=0; i< sampleSize; ++i )
	{
		float phi = 2.0f * PI * squareSamples[i].u();
		float theta = acos( pow( (1-squareSamples[i].v() ), 1.0/(e + 1) ) );
		float sinTheta = sin (theta);
		float cosTheta = cos (theta);
		float sinPhi = sin (phi);
		float cosPhi = cos (phi);
		Vector p= Vector(1,0,0,0) * sinTheta * cosPhi + Vector(0,0,1,0)* sinTheta * sinPhi + Vector(0,1,0,0) * cosTheta ;
		o_samples.push_back(p);
	}
}
}//end of namespace
