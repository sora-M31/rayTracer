#ifndef _GEO_H_
#define _GEO_H_

#include "shape.h"
#include "material.h"

namespace rayTracer
{
// Sphere class
// ==========================================================
class Sphere:public Shape
{
public:
	Sphere( const Vector& _pos, float _radius );
	Sphere( const Vector& _pos, float _radius, const Material* _material);
	Sphere();
	~Sphere();

	const Vector& Center() const { return m_position; }
	float Radius() const { return m_radius; }
	float RadiusSquared() const { return m_radiusSquared; }

	bool Intersect( const Ray& _ray, Intersection& o_intersection ) const;
    void ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const;
private:
	float  m_radius;
	float  m_radiusSquared;
};
// Plane class
// ==========================================================
class Plane:public Shape
{
public:
	Plane( const Vector& _normal,
		   float _distance,
		   const Material* _material=0 );
	Plane();
	~Plane();

	const Vector& Normal() const { return m_normal; }
	float Distance() const { return m_distance; }

	bool Intersect(const Ray& _ray, Intersection& o_intersection) const;
    void ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const;
private:
	Vector m_normal;
	float m_distance;
};//end of class
}//end of namespace
#endif //end of define
