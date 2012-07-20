#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
int main()
{
#if 1
	rayTracer::Camera cam( 0.3, 7, 1 );
    rayTracer::Scene scene( cam );
    rayTracer::RayTracer raytracer( &scene );
	//raytracer.SetDepthOfField(5);
	//raytracer.SetAntialias(10);
    for(uint32_t i=0; i< 10; i +=1)
    {
        scene.Update(i);
        // Cast rays into scene and write to image
        //raytracer.CastRay( i, 800, 600 );
        raytracer.CastRay( i, 200, 150 );
        //raytracer.CastRay( i, 400, 300 );
        std::cout<<"frame "<<i<<"\n";
    }
#endif
    return EXIT_SUCCESS;
}
