#include "raytracer.h"
#include "scene.h"
#include <math.h>
int main()
{
    rayTracer::Scene scene;
    rayTracer::RayTracer raytracer ( &scene );
    for(float i=0; i< 50; i +=1)
    {
        std::cout<<"frame "<<i<<"\n";
        scene.Update(i);
        // Cast rays into scene and write to image
        raytracer.CastRay(i);
    }
    return EXIT_SUCCESS;
}
