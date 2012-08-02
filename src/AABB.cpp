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
AABB::AABB( const AABB& _other )
: m_min( _other.m_min ),
  m_max( _other.m_max)
{
}
//------------------------------------------------------------------------------
AABB& AABB::operator = ( const AABB& _other )
{
    m_min = _other.m_min;
    m_max = _other.m_max;
    return *this;
}
//------------------------------------------------------------------------------
AABB AABB::Update( const Matrix& _matrix ) const
{
    //return AABB( m_min * _matrix, m_max * _matrix );
    // from real time collision detection book, sample form [http://books.google.co.uk/books?id=WGpL6Sk9qNAC&pg=PA86&lpg=PA86&ots=Pm0VkH0feJ&dq=transform+aabb#v=onepage&q=transform%20aabb&f=false]
    Vector min( 0,0,0,1 );
    Vector max( 0,0,0,1 );
    for( uint8_t i=0; i<3; ++i )
    {
        min[i] = _matrix[i][3] - EPSILON;
        max[i] = _matrix[i][3] + EPSILON;
        for( uint8_t j=0; j<3; ++j )
        {
            float e = _matrix[i][j] * m_min[j];
            float f = _matrix[i][j] * m_max[j];
            if ( e < f )
            {
                min[i] += e;
                max[i] += f;
            }
            else
            {
                max[i] += e;
                min[i] += f;
            }
        }
    }
    return AABB( min, max );
}
//------------------------------------------------------------------------------
bool AABB::Intersect( const Ray& _ray, float& o_min, float& o_max ) const
{
#if 0
    float rayDis = FLT_MAX;
    //test the min faces
    float epsilon = -0.1;
    for( uint8_t i=0; i< 3; ++i )
    {
        float dis = ( m_min[i] - _ray.Origin()[i] )/ _ray.Direction()[i];
        if ( dis < epsilon )
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
        if ( dis < epsilon )
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
    //o_rayDis = rayDis;
    o_min = rayDis;
    return rayDis < FLT_MAX;
#endif
#if 1
    //float tmin(FLT_MAX);
    //float tmax(-FLT_MAX);
    float tmin(-FLT_MAX);
    float tmax(FLT_MAX);
    for( uint32_t i=0; i< 3; ++i )
    {
        float disMin( -FLT_MAX );
        float disMax( FLT_MAX );
        //min = ray.o + dis *dir;
        if( ! RealCompare( _ray.Direction()[i], 0, 0.000001 ) )
        {
            disMin = ( m_min[i] - _ray.Origin()[i] )/ _ray.Direction()[i];
            disMax = ( m_max[i] - _ray.Origin()[i] )/ _ray.Direction()[i];
        }
        tmin = std::max( tmin, std::min(disMin, disMax) );
        tmax = std::min( tmax, std::max(disMin, disMax) );
    }
    if( tmax >= tmin )
    {
        o_min = tmin;
        o_max = tmax;
        return true;
    }
    return false;
#endif
}
}//end of space
