#include "camera.h"

namespace rayTracer
{
Camera::Camera ()
{
    m_transform.AsIdentity();
    m_worldToCamera.AsIdentity();
}
//------------------------------------------------------------------------------
Camera::Camera ( const Matrix& _transform )
: m_transform ( _transform )
{
    m_worldToCamera = m_transform.Inverse ();
}
//------------------------------------------------------------------------------
Camera::~Camera()
{}
//------------------------------------------------------------------------------
Vector Camera::ToCameraSpace ( const Vector& _worldPosition )
{
    return m_worldToCamera * _worldPosition;
}
}
