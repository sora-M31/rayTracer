#include "ray.h"

namespace rayTracer
{
//------------------------------------------------------------------------
Ray::Ray ( const Vector& _origin,
           const Vector& _direction,
           const Shape* _pShape )
: m_origin ( _origin ),
  m_direction ( _direction ),
  m_pShape ( _pShape )
{
    Normalise ( m_direction );
}
//------------------------------------------------------------------------
Ray::Ray ( const Ray& _otherRay )
: m_origin ( _otherRay.m_origin ),
  m_direction ( _otherRay.m_direction ),
  m_pShape ( _otherRay.m_pShape )
{}
//------------------------------------------------------------------------
Vector Ray::GetPosition ( float _rayParameter ) const
{
    return m_origin + m_direction * _rayParameter;
}
}

