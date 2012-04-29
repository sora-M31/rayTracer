#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_
#include <float.h>
#include "vector.h"

namespace rayTracer
{
class Shape;
class Intersection
{
public:
	Intersection ();
	Intersection ( const Vector& _position,
				   const Vector& _normal,
				   float _rayParameter,
				   const Shape* _pShape );
	Intersection ( const Intersection& other );
	Intersection& operator = (const Intersection& other);

	const Vector& Position () const { return m_position; }
	const Vector& Normal () const { return m_normal; }
	float RayParameter () const { return m_rayParameter; }
	const Shape* GetShape() { return m_pShape;}

	//if not hit the edge, there's intersection
	bool Intersected() const { return m_rayParameter != FLT_MAX; }
private:
	///\ position of the intersection
	Vector m_position;
	///\ normal at the intersection
	Vector m_normal;
	///\ distance from ray origin
	float m_rayParameter;
	//const Shape* m_pShape;
	const Shape* m_pShape;
};//end of class
}//end of namespace
#endif //end of define
