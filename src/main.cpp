#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
#include <time.h>
int main()
{
#if 1
	rayTracer::Camera cam( 0.3, 5, 60 );
	cam.SampleLens(3);
    rayTracer::Scene scene( cam );
    rayTracer::RayTracer raytracer( &scene, 100, 75  );
    //rayTracer::RayTracer raytracer( &scene, 800, 600  );
	raytracer.SetDepthOfField(3);
	//raytracer.SetAntialias(3);
	raytracer.CreateRays();
	//time_t start, end;
//    for(uint32_t i=0; i< 144; i +=1)
    for(uint32_t i=0; i< 1; i +=1)
    {
		//time(&start);
        scene.Update(i);
        // Cast rays into scene and write to image
		//if(i==4)
        raytracer.CastRay( i, -1);
        //raytracer.CastRay( i,100,75, -1);
		//}
		//time(&end);
        std::cout<<"frame "<<i<<"\n";
        //std::cout<<"using "<<difftime(end,start)<<"\n";
    }
#endif
    return EXIT_SUCCESS;
}
