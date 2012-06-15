#include "mesh.h"
#include "float.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
Triangle Triangle::operator * ( const Matrix& _matrix ) const
{
	return Triangle( m_vertex[0] * _matrix, m_vertex[1] * _matrix, m_vertex[2] * _matrix,
					 m_normal[0] * _matrix, m_normal[1] * _matrix, m_normal[2] * _matrix, s_id );
}
//------------------------------------------------------------------------------
Triangle::Triangle ( const Triangle& _other )
{
	m_vertex.push_back(_other.m_vertex[0]);
	m_vertex.push_back(_other.m_vertex[1]);
	m_vertex.push_back(_other.m_vertex[2]);
	m_normal.push_back(_other.m_normal[0]);
	m_normal.push_back(_other.m_normal[1]);
	m_normal.push_back(_other.m_normal[2]);
	s_id = _other.s_id;
}
//------------------------------------------------------------------------------
Triangle& Triangle::operator = ( const Triangle& _other )
{
	m_vertex[0] = _other.m_vertex[0];
	m_vertex[1] = _other.m_vertex[1];
	m_vertex[2] = _other.m_vertex[2];
	m_normal[0] = _other.m_normal[0];
	m_normal[1] = _other.m_normal[1];
	m_normal[2] = _other.m_normal[2];
	s_id = _other.s_id;
	return *this;
}
//------------------------------------------------------------------------------
//from[http://www.flipcode.com/archives/Raytracing_Topics_Techniques-Part_7_Kd-Trees_and_More_Speed.shtml]
bool Triangle::Intersect( const Ray& _ray, Intersection& o_intersection ) const
{
	/*      v0
		/\
	 b /   \c
	v1/_____\ v2
		a
	*/
	Vector b = m_vertex[1] - m_vertex[0];
	Vector c = m_vertex[2] - m_vertex[0];
	Vector normal = b.Cross (c);
	if( RealCompare( normal.Dot(normal), 0.0f, 0.00000000001 ) )
		return false;
	Normalise(normal);

	float rayParameter = normal.Dot ( m_vertex[0] - _ray.Origin () ) / normal.Dot ( _ray.Direction () );
	//no intersection on the plane ( pointing away or parallel )
	if ( rayParameter < 0.0f )
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
	Vector diff = intersectionPos - m_vertex[0];
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
	float p1 = 1.0 - p2 - p3;
	Vector averageNormal = p1 * m_normal[0] + p2 * m_normal[1] + p3 * m_normal[2];
	Normalise(averageNormal);
	
	o_intersection = Intersection ( intersectionPos, averageNormal, rayParameter,0 );
	//o_intersection = Intersection ( intersectionPos, normal, rayParameter,0 );
	return true;
}
//------------------------------------------------------------------------------
Mesh::~Mesh ()
{}
//------------------------------------------------------------------------------
Mesh::Mesh ( const Vector& _pos, const ObjLoader& _obj, Material* _pMaterial )
: m_tree(5, &m_transform)
{
	m_position = _pos;
	m_pMaterial = _pMaterial;
	m_transform = Matrix ( 1, 0, 0, _pos.x(),
						   0, 1, 0, _pos.y(),
						   0, 0, 1, _pos.z(),
						   0, 0, 0, 1 );
#if 1
	uint32_t size = _obj.GetVertexArray().size();
	m_tree.m_data.reserve(size);
	for(uint32_t i=0; i< size; i+=3 )
	{
		m_tree.m_data.push_back( Triangle( _obj.GetVertexArray()[i], _obj.GetVertexArray()[i+1], _obj.GetVertexArray()[i+2],
								  _obj.GetNormalArray()[i], _obj.GetNormalArray()[i+1], _obj.GetNormalArray()[i+2] , i/3.0) );
#if 0
		std::cout<<_obj.GetVertexArray()[i]<<" ";
		std::cout<<_obj.GetVertexArray()[i+1]<<" ";
		std::cout<<_obj.GetVertexArray()[i+2]<<"\n";
#endif
#if 0
		std::cout<<_obj.GetNormalArray()[i]<<" ";
		std::cout<<_obj.GetNormalArray()[i+1]<<" ";
		std::cout<<_obj.GetNormalArray()[i+2]<<"\n";
#endif
	}
	m_tree.Init();
	#if 0
	for(uint32_t i=0; i< m_tree.m_data.size(); ++i )
	{
		 m_tree.m_data[i].Print();
	}
#endif
	
	m_tree.Transform( & m_transform);
	uint32_t depth=0;
	m_tree.BuildTree( m_tree.m_root, depth );
#endif
#if 0
	m_pointArray = _obj.GetVertexArray ( );
	m_normalArray = _obj.GetNormalArray ( );
#endif
}
//------------------------------------------------------------------------------
void Mesh::PrintData () const
{
#if 0
	for ( uint32_t i=0;i< m_pointArray.size ( ); ++i )
	{
		Vector t = m_pointArray[i];
	}
	for ( uint32_t i=0 ;i< m_normalArray.size ( ); ++i )
	{
		Vector t = m_normalArray[i];
	}
#endif
}
//------------------------------------------------------------------------------
bool Mesh::Intersect ( const Ray& _ray, Intersection& o_intersection ) const
{
	//intersect kd tree
	bool result = m_tree.Intersect( m_tree.m_root, _ray, o_intersection );
	if(result )
	{
		o_intersection.SetMaterial( m_pMaterial );
	}
	
	//set material
#if 0
	if (  m_pointArray.size () != 0 && m_normalArray.size () !=0 )
	{
		
		float parameter = FLT_MAX;
		for ( uint32_t i=0; i< m_pointArray.size () ;i+=3 )
		{
			RayTriangle ( _ray, m_transform * m_pointArray[i], m_transform * m_pointArray[i+1], m_transform * m_pointArray[i+2], _intersection, parameter );
		}
		return (  _intersection.RayParameter () < FLT_MAX );
	}
	else
		return false;
#endif
		return false;
}
//------------------------------------------------------------------------------
void Mesh::ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const
{}
}//end of namespace
