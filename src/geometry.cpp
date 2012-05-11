#include "geometry.h"
#include "util.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Sphere::Sphere( const Vector& _pos, float _radius )
: m_radius( _radius )
{
    m_position = _pos;
    m_radiusSquared = _radius * _radius;
}
//------------------------------------------------------------------------------
Sphere::Sphere( const Vector& _pos,
                float _radius,
                const Material* _material )
: m_radius( _radius )
{
    m_position = _pos;
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
	if ( _ray.Direction().Dot( Vector( m_position - _ray.Origin() ) ) < 0 )
	    return false;

	Vector p = m_position - _ray.Origin();
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
		Vector normal = ( position - Center() ).Normalise();
		o_intersection =  Intersection( position, normal, rayParameter, g_air );
		//inside intersection;
		return true;
	}
		
	rayParameter = pDotRayDir - sqrtf( temp );
	Vector position = _ray.GetPosition( rayParameter );
	Vector normal = ( position - Center() ).Normalise();
	o_intersection =  Intersection( position, normal, rayParameter, m_pMaterial );
	return true;
}
//------------------------------------------------------------------------------
void Sphere::ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const
{}
//------------------------------------------------------------------------------
Plane::Plane( const Vector& _normal,
			  float _distance,
			  Material* _material )
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

	o_intersection =  Intersection( position, m_normal, rayParameter, m_pMaterial);
	return true;
}
//------------------------------------------------------------------------------
void Plane::ToUVSpace( const Vector& _pos, float& o_u, float& o_v ) const
{
		o_u = _pos.Dot( m_u )/30 ;
		o_v = _pos.Dot( m_v )/30 ;
}
//------------------------------------------------------------------------------
}//end of namespace
