#ifndef _UTIL_H_
#define _UTIL_H_

#include <list>
#include <string>
#include "material.h"

namespace rayTracer
{
class Vector;
class Vector2D;
#define AIR_INDEX  1.00028f
#define GLASS_INDEX 1.52f
#define EPSILON 0.001
#define PI  3.14159265
static Material* const g_air = new Material( 0, 0, 0, 0, 1, 0,AIR_INDEX,0 );
void SampleSquare( std::vector<Vector2D>& o_samples, uint32_t _num );
void SampleHemisphere ( std::vector<Vector>& o_samples, uint32_t _num, uint32_t _exp );
// --------------------------------------------------------------------------
void Clamp( float& io_value, float _min, float _max );
// --------------------------------------------------------------------------
float min( const float& _a, const float& _b, const float& _c );
// --------------------------------------------------------------------------
float max( const float& _a, const float& _b, const float& _c );
// --------------------------------------------------------------------------
bool RealCompare( const float& _a, const float& _b, const float& _epsilon);
}
#endif
