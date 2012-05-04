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
    RayTracer();
    ~RayTracer();
    Intersection Intersect ( const Ray& _ray );
    Color Trace( const Ray& _ray, int _depth, std::ofstream& o_output );
    void CastRay();

private:
    Scene m_scene;
    bool m_antialias;
    bool m_depthOfField;
    bool m_softShadow;
    bool m_differentGeo;
};//end of class
}//end of namespace
#endif //end of define
