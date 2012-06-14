#ifndef _AABB_H_
#define _AABB_H_

#include "vector.h"
#include "ray.h"

namespace rayTracer
{
class AABB
{
public:
    AABB();
    AABB( float xmin,  float ymin, float zmin, float xmax, float ymax, float zmax );
    AABB( const Vector& _min, const Vector& _max );
    AABB( const AABB& _other );
    AABB& operator = ( const AABB& _other );
    AABB operator * ( const Matrix& _matrix ) const;
    ~AABB();

    bool Intersect( const Ray& _ray, float& o_rayDis ) const;

    void SetMin(uint32_t _index, float _value) { m_min[_index] = _value; }
    void SetMax(uint32_t _index, float _value) { m_max[_index] = _value; }

    void SetMin ( const Vector& _max ) { m_max = _max; }
    void SetMax ( const Vector& _min ) { m_min = _min; }
    const Vector& Min() const { return m_min; }
    const Vector& Max() const { return m_max; }
    Vector Centre() const { return ( m_min + m_max ) / 2.0f ; }

private:
    Vector m_min;
    Vector m_max;
};
}//end of namespace
#endif //end of define
