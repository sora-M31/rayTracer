#ifndef _MESH_H_
#define _MESH_H_

#include "shape.h"
#include "objLoader.h"
#include "kdTree.h"
#include "util.h"

namespace rayTracer
{
class Triangle
{
public:
	Triangle(){};
	Triangle( const Vector& _v1, const Vector& _v2, const Vector& _v3,
			  const Vector& _n1, const Vector& _n2, const Vector& _n3 )
	{
		m_vertex.push_back( _v1 );
		m_vertex.push_back( _v2 );
		m_vertex.push_back( _v3 );
		m_normal.push_back( _n1 );
		m_normal.push_back( _n2 );
		m_normal.push_back( _n3 );
	};
	Triangle& operator = ( const Triangle& _other );
	~Triangle(){};
	Vector Position() const{ return (m_vertex[0] + m_vertex[1] + m_vertex[2])/3.0; }
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
	uint32_t s_id;
private:
	std::vector<Vector> m_vertex;
	std::vector<Vector> m_normal;
};
//------------------------------------------------------------------------------
class Mesh : public Shape
{
public:
    Mesh ( const Vector& _pos, const ObjLoader& _obj, Material* _pMaterial = 0);
    ~Mesh ();
	void PrintData () const;
	bool Intersect ( const Ray& _ray, Intersection& o_intersection ) const;
    void ToUVSpace( const Vector& _pos, float& o_u, float& o_v )  const;

private:
	KdTree<Triangle> m_tree;
	//std::vector<Vector> m_pointArray;
	std::vector<Vector> m_normalArray;
};//end of class
}//end of namespace
#endif
