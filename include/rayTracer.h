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
    RayTracer( Scene* _pScene, uint32_t _width, uint32_t _height );
    ~RayTracer();
	void CreateRays();
	void CastRay( uint32_t _frame, float _exposure );
	void SetScene( const Scene* _pScene ) { m_pScene = _pScene; }
	void CastRay( uint32_t _frame, uint32_t _width, uint32_t _height, float _exposure );
	void SetAntialias( uint32_t _sampleNum ) { m_antialias = _sampleNum; }
	void SetDepthOfField( uint32_t _sampleNum ) { m_depthOfField = _sampleNum; }

private:
    Intersection IntersectScene( const Ray& _ray );
    Color Trace( const Ray& _ray, int _depth, std::ofstream& o_output );
	Color AmbientOcc( const Intersection& _intersection );
	Color GlossyReflection( const Intersection& _intersection, const Vector& _viewingDir, int _depth, std::ofstream& o_output );
	Color Fresnel( const Intersection& _intersection, const Ray& _ray, int _depth, std::ofstream& o_output );
	float Specular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir );
	float AnisotropicSpecular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir );
	Vector MirrorReflection( const Intersection& _intersection, const Vector& _inDir );
	const Scene* m_pScene;
	uint32_t m_antialias;
    uint32_t m_depthOfField;
	std::vector<Ray> m_rayList;
	uint32_t m_width;
	uint32_t m_height;

};//end of class
}//end of namespace
#endif //end of define
