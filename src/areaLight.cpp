#include "areaLight.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
AreaLight::AreaLight(const Vector& _position, float _intensity, Vector _normal, float _width, float _height)
: m_normal ( _normal),
  m_width ( _width ),
  m_height ( _height )
{
	Normalise ( _normal );
    m_position = _position;
    m_intensity = _intensity;

    Sampling( m_position, m_width, m_height,8,8,Vector(0,0,1,0), m_normal.Cross(Vector(0,0,1,0)), m_lightSamples );
}
//------------------------------------------------------------------------------
AreaLight::~AreaLight()
{}
//------------------------------------------------------------------------------
void AreaLight::GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, float& o_attenuation ) const
{
	std::list<Vector>::const_iterator iter = m_lightSamples.begin ();
	
	while( iter != m_lightSamples.end() )
	{
		Vector lightDir = *iter - _intersection.Position();
		float dis = lightDir.Length ();
		o_attenuation = m_intensity / ( dis * dis );
		Normalise( lightDir );

		o_shadowRays.push_back ( Ray ( _intersection.Position () + _intersection.Normal () * EPSILON, lightDir, 0 ) );
		++iter;
	}
}
}
