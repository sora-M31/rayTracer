#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "ray.h"
#include "util.h"
#include "intersection.h"
#include "shape.h"
#include "color.h"

namespace rayTracer
{
typedef std::list<Ray> RayList;
typedef std::list<float> DisList;
class Light : public Shape
{
public:
	Light ( const Vector& _position, float _intensity, const Color& _color )
	: m_intensity ( _intensity )
	{
		m_translation = _position;
		m_color = _color;
	}
	Light() {}
	~Light() {}

	const float& Intensity () const { return m_intensity; }
	const Color& GetColor() const { return m_color; }
	void SetColor( const Color& _color ) { m_color = _color; }
	virtual void GetShadowRay ( const Intersection& _intersection, RayList& o_shadowRays, DisList& o_disList, float& o_attenuation ) const = 0;

	bool Intersect(const Ray& _ray, Intersection& o_intersection ) const { return false; }

protected:
	float m_intensity;
	Color m_color;
};
}//end of namespace
#endif
