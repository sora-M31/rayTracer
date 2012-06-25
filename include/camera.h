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
	Camera ( float _aperture = 0.2, float _focalLength = 10, float _viewDistance = 1);
    ~Camera();

    virtual bool Intersect ( const Ray& _ray, Intersection& o_intersection ) const{ return false; }
    virtual void ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const{};

    void SampleLens( float _unitNumber );
    Vector RayDirection( float _dx, float _dy, const Vector& _lensSample ) const;
	void Transform( const Matrix& _transform){}

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
    Matrix m_worldToCamera;
	std::list<Vector> m_lenSample;
};//end of class
}//end of namespace
#endif //end of define
