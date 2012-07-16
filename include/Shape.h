#ifndef _SHAPE_H_
#define _SHAPE_H_

#include "vector.h"
#include "ray.h"
#include "intersection.h"
#include "quaternion.h"

namespace rayTracer
{
class material;
class Shape
{
public:
    Shape()
    : m_pMaterial (0)
    {
	}
    ~Shape(){};

    virtual void SetMaterial ( const Material* _material) { m_pMaterial = _material; }
    const Material* GetMaterial () const { return m_pMaterial; }

    Vector Position () const { return Vector ( m_transformation[0][3], m_transformation[1][3], m_transformation[2][3], 1.0); }
    //Vector Position () const { return Vector ( LocalTransformation()[0][3], LocalTransformation()[1][3], LocalTransformation()[2][3], 1.0); }
	Matrix LocalTransformation() const { return Matrix( 1,0,0,m_translation.x(), 0,1,0,m_translation.y(), 0,0,1,m_translation.z(), 0,0,0,1 ) * m_rotation.AsMatrix(); }
	//Matrix LocalTransformation() const { return m_rotation.AsMatrix() * Matrix( 1,0,0,m_translation.x(), 0,1,0,m_translation.y(), 0,0,1,m_translation.z(), 0,0,0,1 ) ; }
	virtual void ToCameraSpace( const Matrix& _transform ) { m_transformation = _transform; }

	void Translate( const Vector& _pos) { m_translation = _pos ; }
	void Rotate( float _angle, const Vector& _axis ) { m_rotation = Quaternion(_angle, _axis); }

    virtual bool Intersect ( const Ray& _ray, Intersection& o_intersection ) const = 0;
    //virtual void ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const = 0;

protected:
    const Material* m_pMaterial;
    //Vector m_u;
    //Vector m_v;
    Vector m_translation;
    Quaternion m_rotation;
	Matrix m_transformation;
};//end of class
}//end of namespace
#endif //end of define
