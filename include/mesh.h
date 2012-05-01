#ifndef _MESH_H_
#define _MESH_H_

#include "shape.h"
#include "objLoader.h"

namespace rayTracer
{
class Mesh : public Shape
{
public:
    Mesh ();
    ~Mesh ();
	bool LoadMesh ( const ObjLoader& _obj );
	void PrintData () const;
	bool Intersect ( const Ray& _ray, Intersection& o_intersection ) const;
	bool RayTriangle ( const Ray& _ray, const Vector& _v1, const Vector& _v2, const Vector& _v3, Intersection& o_intersection, float& o_parameter ) const;

private:
	std::vector<Vector> m_pointArray;
	std::vector<Vector> m_normalArray;
};//end of class
}//end of namespace
#endif
