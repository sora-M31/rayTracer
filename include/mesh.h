#ifndef _MESH_H_
#define _MESH_H_

#include "shape.h"
#include "objLoader.h"
#include "kdTree.h"
#include "util.h"
#include "geometry.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
class Mesh : public Shape
{
public:
	Mesh ( const Vector& _pos, const ObjLoader& _obj, Material* _pMaterial = 0);
	~Mesh ();
	void PrintData () const;
	bool Intersect(const Ray& _ray, Intersection& o_intersection ) const;
	void ToUVSpace( const Vector& _pos, float& o_u, float& o_v )  const;
	void ToCameraSpace( const Matrix& _transform );
	void SetMaterial( const Material* _pMaterial );

private:
	KdTree<Triangle> m_tree;
	//std::vector<Vector> m_pointArray;
	std::vector<Vector> m_normalArray;
};//end of class
}//end of namespace
#endif
