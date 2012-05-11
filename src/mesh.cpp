#include "mesh.h"
#include "float.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Mesh::Mesh ()
{}
//------------------------------------------------------------------------------
Mesh::~Mesh ()
{}
//------------------------------------------------------------------------------
Mesh::Mesh ( const Vector& _pos, const Material* _pMaterial)
{
	m_position = _pos;
	m_pMaterial = _pMaterial;
}
//------------------------------------------------------------------------------
bool Mesh::LoadMesh ( const ObjLoader& _obj )
{
	m_pointArray = _obj.GetVertexArray ( );
	m_normalArray = _obj.GetNormalArray ( );
	if (  m_pointArray.size ( ) == 0 || m_normalArray.size ( ) == 0 )
		return false;
	else
		return true;
}
//------------------------------------------------------------------------------
void Mesh::PrintData () const
{
	for ( uint32_t i=0;i< m_pointArray.size ( ); ++i )
	{
		Vector t = m_pointArray[i];
	}
	for ( uint32_t i=0 ;i< m_normalArray.size ( ); ++i )
	{
		Vector t = m_normalArray[i];
	}
}
//------------------------------------------------------------------------------
bool Mesh::Intersect ( const Ray& _ray, Intersection& _intersection ) const
{
	if (  m_pointArray.size () != 0 && m_normalArray.size () !=0 )
	{
		
		float parameter = FLT_MAX;
		for ( uint32_t i=0; i< m_pointArray.size () ;i+=3 )
		{
			RayTriangle ( _ray, m_pointArray[i], m_pointArray[i+1], m_pointArray[i+2], _intersection, parameter );
		}
		return (  _intersection.RayParameter () < FLT_MAX );
	}
	else
		return false;
}
//------------------------------------------------------------------------------
//from[http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_7_Kd-Trees_and_More_Speed.shtml]
bool Mesh::RayTriangle ( const Ray& _ray, const Vector& _v1, const Vector& _v2, const Vector& _v3, Intersection& o_intersection, float& o_parameter ) const
{
	/*      v1
		/\
	 b /   \c
	v2/_____\ v3
		a
	*/
	Vector b = _v2 - _v1;
	Vector c = _v3 - _v1;
	Vector normal = b.Cross (c);
	Normalise(normal);

	float rayParameter = normal.Dot ( _v1 - _ray.Origin () ) / normal.Dot ( _ray.Direction () );
	//no intersection on the plane ( pointing away or parallel )
	if ( rayParameter < 0.0f || rayParameter > FLT_MAX )
	{
		return false;
	}
	// if on the plane but farther than the previous intersection
	if (  rayParameter > o_parameter )
	{
		return false;
	}

	//if on the plane
	//solve the problem on 2d
	//get dominant axis of normal
    uint8_t axis = normal.DominantAxis();
	// p = p1*v1 + p2*v2 + p3*v3
	// p1+ p2+ p3 =1
	// p2 (  v2 - v1 ) + p3 (  v3 - v1 ) = intersection - v1
	Vector intersectionPos = _ray.Origin () + rayParameter * _ray.Direction ();
	Vector diff = intersectionPos - _v1;
	float bU, bV, cU, cV, diffU, diffV;
	uint8_t axisU = ( axis + 1 )%3;
	uint8_t axisV = ( axis + 2 )%3;
	diffU = diff[axisU];
	diffV = diff[axisV];
	bU = b[axisU];
	bV = b[axisV];
	cU = c[axisU];
	cV = c[axisV];
	float tmp =  bU * cV - bV * cU ;
	float p2 = (  cV * diffU - cU * diffV ) / tmp;
	if ( p2<0.0 )
	{
		return false;
	}
	float p3 = (  bU * diffV - bV * diffU ) / tmp;
	if (  p3<0.0 )
	{
		return false;
	}
	if (  p2+ p3> 1.0 )
	{
		return false;
	}
	o_intersection = Intersection ( intersectionPos, normal, rayParameter, m_pMaterial );
	o_parameter = rayParameter;
	return true;
}
//------------------------------------------------------------------------------
void Mesh::ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const
{}
}//end of namespace
