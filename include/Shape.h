#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "vector.h"
#include "ray.h"
#include "intersection.h"

namespace rayTracer
{
class material;
class Shape
{
public:
    Shape()
    : m_pMaterial (0)
    {}
    ~Shape(){};

    const Vector& Position () const { return m_position; }
    void SetMaterial ( const Material* _material) { m_pMaterial = _material; }
    const Material* GetMaterial () const { return m_pMaterial; }
    virtual bool Intersect ( const Ray& _ray, Intersection& o_intersection ) const = 0;
    virtual void ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const = 0;

protected:
    Vector m_position;
    const Material* m_pMaterial;
    Vector m_u;
    Vector m_v;
    Matrix m_transform;
};//end of class
}//end of namespace
#endif //end of define
