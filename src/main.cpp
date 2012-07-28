#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
#include <time.h>
int main( int argc, const char* argv[] )
{
	int width = atoi(argv[1]);
	int height = atoi(argv[2]);
	int start = atoi(argv[3]);
	int end = atoi(argv[4]);
	rayTracer::Camera cam( 0.3, 5, 60 );
	//cam.SampleLens(3);
    rayTracer::Scene scene( cam );
    //rayTracer::RayTracer raytracer( &scene, 400,300  );
    rayTracer::RayTracer raytracer( &scene, width, height );
	//raytracer.SetDepthOfField(3);
	raytracer.SetAntialias(3);
	raytracer.CreateRays();
    for(uint32_t i=start; i< end; i +=1)
    {
        scene.Update(i);
        // Cast rays into scene and write to image
        raytracer.CastRay( i, -2.5);
        std::cout<<"frame "<<i<<"\n";
    }
    return EXIT_SUCCESS;
}
