#include "intersection.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
Intersection::Intersection()
: m_rayParameter ( FLT_MAX ),
  m_pShape (0)
{}
//------------------------------------------------------------------------------
Intersection::Intersection ( const Vector& _position,
                             const Vector& _normal,
                             float _rayParameter,
                             const Shape* _pShape )
: m_position ( _position ),
  m_normal ( _normal ),
  m_rayParameter ( _rayParameter ),
  m_pShape ( _pShape )
{}
//------------------------------------------------------------------------------
Intersection::Intersection ( const Intersection& _other )
: m_position ( _other.m_position ),
  m_normal ( _other.m_normal ),
  m_rayParameter ( _other.m_rayParameter ),
  m_pShape ( _other.m_pShape )
{
}
//------------------------------------------------------------------------------
Intersection& Intersection::operator = (const Intersection& other)
{
    m_position = other.m_position;
    m_normal = other.m_normal;
    m_rayParameter = other.m_rayParameter;
    m_pShape = other.m_pShape;
    return *this;
}
}
