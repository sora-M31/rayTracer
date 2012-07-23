#include "areaLight.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
AreaLight::AreaLight(const Vector& _position, float _width, float _height, Vector _normal, uint32_t _sampleNum, float _intensity, const Color& _color )
: m_width( _width ),
  m_height( _height ),
  m_normal ( _normal)
{
    m_translation = _position;
    m_intensity = _intensity/(float)( _sampleNum * _sampleNum);
	m_color = _color;

	//todo rotation
	Normalise ( m_normal );

	std::vector<Vector2D> samples;
    SampleSquare( samples, _sampleNum );
	std::vector<Vector2D>::iterator iter = samples.begin();
	Vector u;
	Vector v;
	m_normal.GetBasis( u, v );
	while( iter != samples.end() )
	{
		m_lightSamples.push_back( Position() + u *(iter->u() - 0.5) * m_width + v*( iter->v() - 0.5 ) * m_height );
		++iter;
	}
	m_lightSamplesTransformed = m_lightSamples;
}
//------------------------------------------------------------------------------
AreaLight::~AreaLight()
{}
//------------------------------------------------------------------------------
void AreaLight::GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, DisList& o_disList, float& o_attenuation ) const
{
	std::vector<Vector>::const_iterator iter = m_lightSamplesTransformed.begin ();
	while( iter != m_lightSamplesTransformed.end() )
	{
		Vector lightDir = *iter - _intersection.Position();
		float dis = lightDir.Length ();
		o_disList.push_back( dis );
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
	for( uint32_t i=0; i< m_lightSamples.size(); ++i )
	{
		m_lightSamplesTransformed[i] = m_lightSamples[i] * _transform; 
	}
}
}
