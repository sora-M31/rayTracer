#ifndef _CAMERA_H_
#define _CAMERA_H_
#include <list>
#include "util.h"
#include "matrix.h"
#include "shape.h"
namespace rayTracer
{
class Camera : public Shape
{
public:
	Camera( float _aperture, float _focalLength, float _fov );
    ~Camera();

    void SampleLens( uint32_t _unitNumber );
    Vector RayDirection( float _dx, float _dy, const Vector& _lensSample ) const;
	const std::vector<Vector>& LensSample() const { return m_lenSample; }
	float ViewPlaneDis() const { return m_viewDistance; }
	void Transform( const Matrix& _transform) {}
    virtual bool Intersect( const Ray& _ray, Intersection& o_intersection ) const{ return false; }

private:
    float m_aperture;
    float m_focalLength;
	float m_viewDistance;
	std::vector<Vector> m_lenSample;
	Vector m_lookat;
	Vector m_up;
};//end of class
}//end of namespace
#endif //end of define
