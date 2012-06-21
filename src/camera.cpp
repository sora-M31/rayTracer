#include "camera.h"

namespace rayTracer
{
Camera::Camera ( float _aperture, float _focalLength, float _viewDistance )
: m_aperture( _aperture ),
  m_focalLength( _focalLength ),
  m_viewDistance( _viewDistance )
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
//------------------------------------------------------------------------------
void Camera::SampleLens( float _unitNumber )
{
		Vector unitX = Vector(1,0,0,0);
		Vector unitY = Vector(0,1,0,0);
		Vector centre = Vector(0,0,0,1);

		Sampling( centre, m_aperture, m_aperture, _unitNumber, _unitNumber, unitX, unitY, m_lenSample );
}
//------------------------------------------------------------------------------
Vector Camera::RayDirection( float _dx, float _dy, const Vector& _lensSample ) const
{
#if 1
	//sample before transformation
	//2d projection
	float focalX = _dx * m_focalLength / m_viewDistance;
	float focalY = _dy * m_focalLength / m_viewDistance ;

	//dir = focalPoint - samplePoint
	Vector sampleRayDir = (focalX - _lensSample.x() ) * Vector(1,0,0,0) +
						  (focalY - _lensSample.x() ) * Vector(0,1,0,0) +
						  m_focalLength * Vector(0,0,1,0);
	return sampleRayDir.Normalise();
#endif
#if 0
	Vector focalPoint = Vector(0, 0, 0, 1.0f) + Vector(_dx, _dy, 1.0f, 0) * m_focalLength;
	Vector dir = (focalPoint - (_lensSample) ).Normalise();
	return dir;
#endif
}
}
