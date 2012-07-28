#include "camera.h"
#include "quaternion.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Camera::Camera( float _aperture, float _focalLength, float _fov )
: m_aperture( _aperture ),
  m_focalLength( _focalLength ),
  m_lookat( Vector(0,0,1,0) ),
  m_up( Vector(0,1,0,0) )
{
	//_fov/2.0 * PI / 180
	m_viewDistance = 0.5 / tan( _fov * PI / 360.0 );
	m_translation = Vector( 0,0,0,1 );
	m_rotation = Quaternion( 1,0,0,0 );
}
//------------------------------------------------------------------------------
Camera::~Camera()
{}
//------------------------------------------------------------------------------
void Camera::SampleLens( float _unitNumber )
{
		std::vector<Vector2D> samples(0);
		SampleSquare( samples, _unitNumber);

		for( size_t i=0; i< samples.size(); ++i )
		{
			m_lenSample.push_back( Vector( ( -0.5 + samples[i].u() )* m_aperture,
										   ( -0.5 + samples[i].v() )* m_aperture,
											 0, 1 ) );
		}
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
						  (focalY - _lensSample.y() ) * Vector(0,1,0,0) +
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
