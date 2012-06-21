#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <list>
#include "util.h"
#include "matrix.h"
namespace rayTracer
{
class Camera
{
public:
	Camera ( float _aperture = 0.2, float _focalLength = 10, float _viewDistance = 1);
    Camera ( const Matrix& _transform );
    ~Camera();

    Vector ToCameraSpace ( const Vector& _worldPosition );
    void SampleLens( float _unitNumber );
    Vector RayDirection( float _dx, float _dy, const Vector& _lensSample ) const;

    const Matrix& Transform() const { return m_transform; }
    const Matrix& WorldTransform() const { return m_worldToCamera; }
	const std::list<Vector>& LensSample() const { return m_lenSample; }
#if 0
	Vector u() const {}
	Vector v() const {}
	Vector w() const {}
#endif
private:
    float m_aperture;
    float m_focalLength;
	float m_viewDistance;
    Matrix m_transform;
    Matrix m_worldToCamera;
	std::list<Vector> m_lenSample;
};//end of class
}//end of namespace
#endif //end of define
