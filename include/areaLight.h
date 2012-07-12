#ifndef _AREALIGHT_H_
#define _AREALIGHT_H_

#include "light.h"
namespace rayTracer
{
class AreaLight: public Light
{
public:
	AreaLight ( const Vector& _position, float _intensity, Vector _normal, uint32_t _sampleNum );
	~AreaLight ();

	void GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, float& o_attenuation ) const;
	Vector Normal();
	void ToCameraSpace( const Matrix& _transform);

private:
	Vector m_normal;
	float m_width;
	float m_height;
	std::vector<Vector> m_lightSamples;
	std::vector<Vector> m_lightSamplesTransformed;
};//end of class
}//end of namespace
#endif //end of define
