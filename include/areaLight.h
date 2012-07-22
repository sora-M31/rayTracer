#ifndef _AREALIGHT_H_
#define _AREALIGHT_H_

#include "light.h"
namespace rayTracer
{
class AreaLight: public Light
{
public:
	AreaLight(const Vector& _position, float _width, float _height, Vector _normal, uint32_t _sampleNum, float _intensity, const Color& _color );
	~AreaLight ();

	void GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, DisList& o_disList, float& o_attenuation ) const;
	Vector Normal();
	void ToCameraSpace( const Matrix& _transform);

private:
	float m_width;
	float m_height;
	Vector m_normal;
	std::vector<Vector> m_lightSamples;
	std::vector<Vector> m_lightSamplesTransformed;
};//end of class
}//end of namespace
#endif //end of define
