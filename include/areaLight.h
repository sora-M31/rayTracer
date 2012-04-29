#ifndef _AREALIGHT_H_
#define _AREALIGHT_H_

#include "light.h"
namespace rayTracer
{
class AreaLight: public Light
{
public:
	AreaLight ( const Vector& _position, float _intensity, Vector _normal, float _width, float _height );
	~AreaLight ();

	void GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, float& o_attenuation ) const;

private:
	Vector m_normal;
	float m_width;
	float m_height;
	std::list<Vector> m_lightSamples;
};//end of class
}//end of namespace
#endif //end of define
