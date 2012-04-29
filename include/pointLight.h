#ifndef _POINTLIGHT_H_
#define _POINTLIGHT_H_

#include "light.h"

namespace rayTracer
{
class PointLight: public Light
{
public:
	PointLight ( const Vector& _position, float _intensity );
	~PointLight ();

	void GetShadowRay (const Intersection& _intersection, RayList& o_shadowRays, float& o_attenuation) const;
};//end of class
}//end of namespace
#endif //end of define


