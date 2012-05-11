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
    Mesh ( const Vector& _pos, const Material* _pMaterial = 0);
	bool LoadMesh ( const ObjLoader& _obj );
	void PrintData () const;
	bool Intersect ( const Ray& _ray, Intersection& o_intersection ) const;
    void ToUVSpace( const Vector& _pos, float& o_u, float& o_v )  const;

private:
	bool RayTriangle ( const Ray& _ray, const Vector& _v1, const Vector& _v2, const Vector& _v3, Intersection& o_intersection, float& o_parameter ) const;
	std::vector<Vector> m_pointArray;
	std::vector<Vector> m_normalArray;
};//end of class
}//end of namespace
#endif
