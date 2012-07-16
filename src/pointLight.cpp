#include "pointLight.h"
#include "util.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
PointLight::PointLight ( const Vector& _position, float _intensity )
{
    m_translation = _position;
    m_intensity = _intensity;
}
//------------------------------------------------------------------------------
PointLight::~PointLight()
{}
//------------------------------------------------------------------------------
void PointLight::GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, DisList& o_disList, float& o_attenuation ) const
{
	Vector lightDir = Position() - _intersection.Position();
	float dis = lightDir.Length();
	o_disList.push_back(dis);
	float attenuation = m_intensity / ( dis*dis );
	Clamp( attenuation, 0, 1);
	o_attenuation = attenuation;
	Normalise( lightDir );

	o_shadowRays.push_back ( Ray ( _intersection.Position() + _intersection.Normal() * EPSILON, lightDir, g_air ) );
}
}//end of namespace
