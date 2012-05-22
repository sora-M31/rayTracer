#include "AABB.h"

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
bool AABB::Intersect( const Ray& _ray )
{
    //if ray origin in the box, intersected
    Vector origin = _ray.Origin();
    if ( origin.x() > m_min.x() && origin.x() < m_max.x() &&
         origin.y() > m_min.y() && origin.y() < m_max.y() &&
         origin.z() > m_min.z() && origin.z() < m_max.z() )
    {
        return true;
    }
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
        return true;
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
        return true;
    }
    return false;
}
}//end of space
