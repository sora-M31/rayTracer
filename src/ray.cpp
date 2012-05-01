#include "ray.h"

namespace rayTracer
{
//------------------------------------------------------------------------
Ray::Ray ( const Vector& _origin,
           const Vector& _direction,
           const Material* _pMaterial )
: m_origin ( _origin ),
  m_direction ( _direction ),
  m_pMaterial ( _pMaterial )
{
    Normalise ( m_direction );
}
//------------------------------------------------------------------------
Ray::Ray ( const Ray& _otherRay )
: m_origin ( _otherRay.m_origin ),
  m_direction ( _otherRay.m_direction ),
  m_pMaterial ( _otherRay.m_pMaterial )
{}
//------------------------------------------------------------------------
Vector Ray::GetPosition ( float _rayParameter ) const
{
    return m_origin + m_direction * _rayParameter;
}
}

