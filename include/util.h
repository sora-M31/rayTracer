#ifndef _UTIL_H_
#define _UTIL_H_

#include <list>
#include <string>
#include "vector.h"
#include "material.h"

namespace rayTracer
{
#define AIR_INDEX  1.00028f
#define GLASS_INDEX 2.50f
static Material* const g_air = new Material( 0, 1, 0,AIR_INDEX );

// --------------------------------------------------------------------------
/// \brief Sampling a rectangle
/// \param centre
/// \param width
/// \param height
/// \param gridNumberU
/// \param gridNumberV
/// \param u unit vector (axis)
/// \param v unit vector (axis)
/// \param samples
void Sampling ( const Vector& _centre, float _width, float _height, float _gridNumberU, float _gridNumberV, const Vector& _u, const Vector& _v, std::list<Vector>& o_samples);
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
