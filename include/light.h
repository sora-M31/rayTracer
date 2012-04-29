#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "ray.h"
#include "util.h"
#include "intersection.h"

namespace rayTracer
{
typedef std::list<Ray> RayList;
class Light
{
public:
	Light ( const Vector& _position, float _intensity )
	: m_position ( _position ),
	  m_intensity ( _intensity )
	{}
	Light() {}
	~Light() {}

	const Vector& Position () const { return m_position; }
	const float& Intensity () const { return m_intensity; }

	virtual void GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, float& o_attenuation ) const = 0;

protected:
	Vector m_position;
	float m_intensity;
};
}//end of namespace
#endif
