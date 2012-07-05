#ifndef _RAYTRACER_H_
#define _RAYTRACER_H_
#include <ostream>
#include "intersection.h"
#include "ray.h"
#include "scene.h"
#include "color.h"
namespace rayTracer
{
class RayTracer
{
public:
    RayTracer( Scene* _pScene =0 );
    ~RayTracer();
	void SetScene( const Scene* _pScene ) { m_pScene = _pScene; }
	void CastRay( uint32_t _frame, uint32_t _width, uint32_t _height );
	void SetAntialias() { m_antialias = true; }
	void SetDepthOfField() { m_depthOfField = true; }

private:
    Intersection IntersectScene ( const Ray& _ray );
    Color Trace( const Ray& _ray, uint32_t _depth, std::ofstream& o_output );
	Color Diffuse( const Intersection& _intersection, const Vector& _lightDir, float _attenuation );
	Color Specular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir, float _attenuation );
	Color MirrorReflection( const Intersection& _intersection, const Vector& _viewingDir, uint32_t _depth, std::ofstream& o_output );
	Color Refraction( const Intersection& _intersection, const Ray& _ray, uint32_t _depth, std::ofstream& o_output );
	Color GlossyReflection( const Intersection& _intersection, const Vector& _viewingDir, uint32_t _depth, std::ofstream& o_output );
	const Scene* m_pScene;
    bool m_antialias;
    bool m_depthOfField;
};//end of class
}//end of namespace
#endif //end of define
