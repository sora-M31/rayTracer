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
    RayTracer( const Scene* _pScene =0 );
    ~RayTracer();
	void SetScene( const Scene* _pScene ) { m_pScene = _pScene; }
    Intersection Intersect ( const Ray& _ray );
    Color Trace( const Ray& _ray, int _depth, std::ofstream& o_output );
    void CastRay( uint32_t _frame);

private:
    //Scene m_scene;
	const Scene* m_pScene;
    bool m_antialias;
    bool m_depthOfField;
    bool m_softShadow;
    bool m_differentGeo;
	std::list<Vector> lenSample;
};//end of class
}//end of namespace
#endif //end of define
