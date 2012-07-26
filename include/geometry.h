#ifndef _GEO_H_
#define _GEO_H_

#include "shape.h"
#include "material.h"
#include "vector2D.h"

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

	bool Intersect(const Ray& _ray, Intersection& o_intersection ) const;
    void ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const;
private:
	Vector m_normal;
	Vector m_u;
	Vector m_v;
	float m_distance;
};//end of class
// ==========================================================
class Triangle:public Shape
{
public:
	Triangle(){};
	Triangle( const Triangle& _other );
	Triangle( const Vector& _v1, const Vector& _v2, const Vector& _v3,
			  const Vector& _n1, const Vector& _n2, const Vector& _n3,
			  const Vector2D& _tex1, const Vector2D& _tex2, const Vector2D& _tex3,
			  const Material* _pMaterial, uint32_t _id)
	{
		m_vertex.push_back( _v1 );
		m_vertex.push_back( _v2 );
		m_vertex.push_back( _v3 );
		m_normal.push_back( _n1 );
		m_normal.push_back( _n2 );
		m_normal.push_back( _n3 );
		m_texture.push_back( _tex1 );
		m_texture.push_back( _tex2 );
		m_texture.push_back( _tex3 );
		m_pMaterial = _pMaterial;
		s_id =_id;
	};
	Triangle& operator = ( const Triangle& _other );
	~Triangle(){};
	bool Intersect( const Ray& _ray, Intersection& o_intersection ) const;
	Triangle operator * ( const Matrix& _matrix ) const;
	void Print() const{ std::cout<<m_vertex[0]<<" "<<m_vertex[1]<<" "<<m_vertex[2]<<"\n"; }
	Vector Min() const { return Vector( min( m_vertex[0].x(), m_vertex[1].x(), m_vertex[2].x() ),
										min( m_vertex[0].y(), m_vertex[1].y(), m_vertex[2].y() ),
										min( m_vertex[0].z(), m_vertex[1].z(), m_vertex[2].z() ), 1.0 ); }
	Vector Max() const { return Vector( max( m_vertex[0].x(), m_vertex[1].x(), m_vertex[2].x() ),
										max( m_vertex[0].y(), m_vertex[1].y(), m_vertex[2].y() ),
										max( m_vertex[0].z(), m_vertex[1].z(), m_vertex[2].z() ), 1.0 ); }
	const std::vector<Vector>& GetVertex() { return m_vertex; }

private:
	uint32_t s_id;
	std::vector<Vector> m_vertex;
	std::vector<Vector> m_normal;
	std::vector<Vector2D> m_texture;
};
}//end of namespace
#endif //end of define
