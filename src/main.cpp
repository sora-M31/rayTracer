#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
int main()
{
	rayTracer::Camera cam( 0.3, 8, 1 );
    rayTracer::Scene scene( cam );
    rayTracer::RayTracer raytracer( &scene );
	//raytracer.SetDepthOfField(5);
	//raytracer.SetAntialias(2);
    for(uint32_t i=0; i< 10; i +=1)
    {
        std::cout<<"frame "<<i<<"\n";
        scene.Update(i);
        // Cast rays into scene and write to image
        raytracer.CastRay( i, 400, 300 );
    }
    return EXIT_SUCCESS;
}
