#include "areaLight.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
AreaLight::AreaLight(const Vector& _position, float _intensity, Vector _normal, float _width, float _height)
: m_normal ( _normal),
  m_width ( _width ),
  m_height ( _height )
{
	Normalise ( m_normal );
    m_translation = _position;
    m_intensity = _intensity;

    Sampling( m_translation, m_width, m_height,8,8,Vector(0,0,1,0), m_normal.Cross(Vector(0,0,1,0)), m_lightSamples );
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
		float attenuation = m_intensity / ( dis * dis );
		Clamp(attenuation, 0, 1);
		o_attenuation = attenuation;
		Normalise( lightDir );

		o_shadowRays.push_back ( Ray ( _intersection.Position () + _intersection.Normal () * EPSILON, lightDir, g_air ) );
		++iter;
	}
}
//------------------------------------------------------------------------------
Vector AreaLight::Normal()
{
	return m_normal * m_transformation;
}
//------------------------------------------------------------------------------
void AreaLight::ToCameraSpace( const Matrix& _transform)
{
	m_lightSamples.clear();
    Sampling( Position(), m_width, m_height,8,8,Vector(0,0,1,0), Normal().Cross(Vector(0,0,1,0)), m_lightSamples );
}
}
