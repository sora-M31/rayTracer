#include "raytracer.h"
#include "scene.h"
int main()
{
    using namespace rayTracer;
    Scene m_scene;
    RayTracer raytracer ( &m_scene );
    raytracer.CastRay(0);
    return EXIT_SUCCESS;
}
