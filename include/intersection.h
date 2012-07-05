#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include <float.h>
#include "vector.h"
#include "vector2D.h"
#include "material.h"

namespace rayTracer
{
class Intersection
{
public:
	Intersection ();
	Intersection ( const Vector& _position,
				   const Vector& _normal,
				   const Vector2D& _texCoord,
				   float _rayParameter,
				   const Material* _pMaterial );
	Intersection ( const Intersection& _other );
	Intersection& operator = (const Intersection& _other);

	const Vector& Position () const { return m_position; }
	const Vector& Normal () const { return m_normal; }
	const Vector2D& TexCoord () const { return m_texCoord; }
	float RayParameter () const { return m_rayParameter; }
	const Material* GetMaterial() const { return m_pMaterial; }
	void SetMaterial( const Material* _pMaterial ) { m_pMaterial = _pMaterial; }
	Color GetColor() const { return m_pMaterial->GetColor( m_texCoord ); }

	//if not hit the edge, there's intersection
	bool Intersected() const { return m_rayParameter != FLT_MAX; }
private:
	///\ position of the intersection
	Vector m_position;
	///\ normal at the intersection
	Vector m_normal;
	Vector2D m_texCoord;
	///\ distance from ray origin
	float m_rayParameter;
	//const Material* m_pMaterial;
	const Material* m_pMaterial;
};//end of class
}//end of namespace
#endif //end of define
