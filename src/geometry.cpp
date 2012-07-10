#include "geometry.h"
#include "util.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Sphere::Sphere( const Vector& _pos, float _radius )
: m_radius( _radius )
{
	Translate( _pos);
    m_radiusSquared = _radius * _radius;
}
//------------------------------------------------------------------------------
Sphere::Sphere( const Vector& _pos,
                float _radius,
                const Material* _material )
: m_radius( _radius )
{
	Translate( _pos);
    m_pMaterial = _material;
    m_radiusSquared = _radius * _radius;
}
//------------------------------------------------------------------------------
Sphere::Sphere()
{}
//------------------------------------------------------------------------------
Sphere::~Sphere()
{}
//------------------------------------------------------------------------------
bool Sphere::Intersect( const Ray& _ray, Intersection& o_intersection ) const
{
	// ray pointing away from sphere
	if ( _ray.Direction().Dot( Vector( Position() - _ray.Origin() ) ) < 0 )
	    return false;

	Vector p = Position() - _ray.Origin();
	float pDotRayDir = p.Dot( _ray.Direction() );

	/* pDotRayDir distance between origin and P's projection on Ray
	  p.Dot( p ) magnitude sqaured of p
	 
	   O,             O,          
		|\             |\         
		| \            |  \        
	   R.  \ p        R.    \     p
		|   \ ,--      |      \ ,-- 
		|   '\         |      '\    
		| '   \        |    '    \
		|'_____.       |___'______ .  
	   Q '   r   P    Q    '   r   P
		  '
		figure 1 )          figure 2 )
	 
	  1 ) rSquared + RSquared = PSquared
	  2 ) rSquared + RSquared < PSquared
	 */
	float temp = m_radiusSquared + pDotRayDir * pDotRayDir - p.Dot( p );
	// no intersection
	if ( temp < 0.0f )
	{
		return false;
	}
	//rayParameter = pDotRayDir - sqrtf( temp );
	float rayParameter;
	// if ray origin is inside sphere
	if ( ( pDotRayDir - sqrtf( temp ) )  < 0.0f )
	{
		rayParameter = pDotRayDir + sqrtf( temp );
		Vector position = _ray.GetPosition( rayParameter );
		Vector normal = ( position - Position() ).Normalise();
		o_intersection =  Intersection( position, normal, Vector2D(0,0), rayParameter, g_air );
		//inside intersection;
		return true;
	}
		
	rayParameter = pDotRayDir - sqrtf( temp );
	Vector position = _ray.GetPosition( rayParameter );
	Vector normal = ( position - Position() ).Normalise();
	o_intersection =  Intersection( position, normal, Vector2D(0,0), rayParameter, m_pMaterial );
	return true;
}
//------------------------------------------------------------------------------
void Sphere::ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const
{}
//------------------------------------------------------------------------------
Plane::Plane( const Vector& _normal,
			  float _distance,
			  const Material* _material )
: m_normal( _normal ),
  m_distance( _distance )
{
	m_pMaterial = _material;
	m_normal.ProjectAxis( m_u, m_v);
}
//------------------------------------------------------------------------------
Plane::Plane()
{}
//------------------------------------------------------------------------------
Plane::~Plane()
{}
//------------------------------------------------------------------------------
bool Plane::Intersect( const Ray& _ray, Intersection& o_intersection) const
{
	float rayParameter = ( m_distance - m_normal.Dot( _ray.Origin() ) ) / m_normal.Dot( _ray.Direction() );

	if (rayParameter < 0.0f)
		return false;

	Vector position = _ray.Origin() + _ray.Direction() * rayParameter;

	o_intersection =  Intersection( position, m_normal,Vector2D(0,0), rayParameter, m_pMaterial );
	return true;
}
//------------------------------------------------------------------------------
void Plane::ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const
{
		o_u = _pos.Dot( m_u )/30 ;
		o_v = _pos.Dot( m_v )/30 ;
}
//------------------------------------------------------------------------------
#if 1
Triangle Triangle::operator * ( const Matrix& _matrix ) const
{
	return Triangle( m_vertex[0] * _matrix, m_vertex[1] * _matrix, m_vertex[2] * _matrix,
					 m_normal[0] * _matrix, m_normal[1] * _matrix, m_normal[2] * _matrix,
					 m_texture[0], m_texture[1], m_texture[2],
					 m_pMaterial, s_id );
}
#endif
//------------------------------------------------------------------------------
Triangle::Triangle ( const Triangle& _other )
{
	m_vertex.push_back(_other.m_vertex[0]);
	m_vertex.push_back(_other.m_vertex[1]);
	m_vertex.push_back(_other.m_vertex[2]);
	m_normal.push_back(_other.m_normal[0]);
	m_normal.push_back(_other.m_normal[1]);
	m_normal.push_back(_other.m_normal[2]);
	m_texture.push_back(_other.m_texture[0]);
	m_texture.push_back(_other.m_texture[1]);
	m_texture.push_back(_other.m_texture[2]);
	m_pMaterial = _other.m_pMaterial;
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
	m_texture[0] = _other.m_texture[0];
	m_texture[1] = _other.m_texture[1];
	m_texture[2] = _other.m_texture[2];
	m_pMaterial = _other.m_pMaterial;
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
	//no intersection on the plane
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
	Vector2D averageTexCoord = p1 * m_texture[0] + p2 * m_texture[1] + p3 * m_texture[2];
	Normalise(averageNormal);
	
	if( m_pMaterial->kRefraction() > 0 && _ray.Direction().Dot( averageNormal ) > 0 )
	{
		//std::cout<<"internal\n";
		o_intersection = Intersection ( intersectionPos, averageNormal, averageTexCoord, rayParameter, g_air );
	}
	else
		o_intersection = Intersection ( intersectionPos, averageNormal, averageTexCoord, rayParameter, m_pMaterial );
	//o_intersection = Intersection ( intersectionPos, normal, rayParameter,0 );
	return true;
}
}//end of namespace
