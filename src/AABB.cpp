#include "AABB.h"
#include <float.h>

namespace rayTracer
{
//------------------------------------------------------------------------------
AABB::AABB()
{}
//------------------------------------------------------------------------------
AABB::~AABB()
{}
//------------------------------------------------------------------------------
AABB::AABB( float _xmin, float _ymin, float _zmin, float _xmax, float _ymax, float _zmax )
: m_min ( Vector ( _xmin, _ymin, _zmin, 1 ) ),
  m_max ( Vector ( _xmax, _ymax, _zmax, 1 ) )
{
}
//------------------------------------------------------------------------------
AABB::AABB( const Vector& _min, const Vector& _max )
: m_min ( _min ),
  m_max ( _max )
{
}
//------------------------------------------------------------------------------
bool AABB::Intersect( const Ray& _ray, float& o_rayDis )
{
    float rayDis = FLT_MAX;
    //test the min faces
    for( uint8_t i=0; i< 3; ++i )
    {
        float dis = ( m_min[i] - _ray.Origin()[i] )/ _ray.Direction()[i];
        if ( dis < 0 )
            continue;
        //get the other two element in the vector
        float v1 = _ray.Origin()[ (i+1)%3 ] + _ray.Direction()[ (i+1)%3 ] * dis;
        float v2 = _ray.Origin()[ (i+2)%3 ] + _ray.Direction()[ (i+2)%3 ] * dis;
        if ( ( v1 < m_min[ (i+1)%3 ] ) || ( v1 > m_max[ (i+1)%3 ] ) )
            continue;
        if ( ( v2 < m_min[ (i+2)%3 ] ) || ( v2 > m_max[ (i+2)%3 ] ) )
            continue;
        if( dis < rayDis )
            rayDis = dis;
    }
    //test max faces
    for( uint8_t i=0; i< 3; ++i )
    {
        float dis = ( m_max[i] - _ray.Origin()[i] )/ _ray.Direction()[i];
        if ( dis < 0 )
            continue;
        //get the other two element in the vector
        float v1 = _ray.Origin()[ (i+1)%3 ] + _ray.Direction()[ (i+1)%3 ] * dis;
        float v2 = _ray.Origin()[ (i+2)%3 ] + _ray.Direction()[ (i+2)%3 ] * dis;
        if ( ( v1 < m_min[ (i+1)%3 ] ) || ( v1 > m_max[ (i+1)%3 ] ) )
            continue;
        if ( ( v2 < m_min[ (i+2)%3 ] ) || ( v2 > m_max[ (i+2)%3 ] ) )
            continue;
        if( dis < rayDis )
            rayDis = dis;
    }
    o_rayDis = rayDis;
    return rayDis < FLT_MAX;
}
}//end of space
