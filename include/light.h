#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "ray.h"
#include "util.h"
#include "intersection.h"
#include "shape.h"

namespace rayTracer
{
typedef std::list<Ray> RayList;
typedef std::list<float> DisList;
class Light : public Shape
{
public:
	Light ( const Vector& _position, float _intensity )
	: m_intensity ( _intensity )
	{
		m_translation = _position;
	}
	Light() {}
	~Light() {}

	const float& Intensity () const { return m_intensity; }
	virtual void GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, DisList& o_disList, float& o_attenuation ) const = 0;

	bool Intersect(const Ray& _ray, Intersection& o_intersection ) const { return false; }

protected:
	float m_intensity;
};
}//end of namespace
#endif
