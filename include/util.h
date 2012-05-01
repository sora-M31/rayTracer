#ifndef _UTIL_H_
#define _UTIL_H_

#include <list>
#include <string>
#include "vector.h"

namespace rayTracer
{
#define EPSILON 0.0001
#define AIR_INDEX  1.00028f
#define GLASS_INDEX 2.00f

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
}
#endif
