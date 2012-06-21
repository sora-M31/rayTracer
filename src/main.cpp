#include "raytracer.h"
#include "scene.h"
int main()
{
    using namespace rayTracer;
    Scene m_scene;
    Camera m_camera;
    m_camera.SampleLens( 8 );
    RayTracer raytracer ( &m_scene, &m_camera );
    raytracer.CastRay(0);
    return EXIT_SUCCESS;
}
