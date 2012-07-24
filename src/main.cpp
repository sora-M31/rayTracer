#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
int main()
{
#if 1
	rayTracer::Camera cam( 0.3, 7, 60 );
    rayTracer::Scene scene( cam );
    rayTracer::RayTracer raytracer( &scene );
	//raytracer.SetDepthOfField(1);
	raytracer.SetAntialias(8);
    for(uint32_t i=0; i< 10; i +=1)
    {
        scene.Update(i);
        // Cast rays into scene and write to image
		//if(i==4)
		//raytracer.CastRay( i, 200, 150, -4 );
		//raytracer.CastRay( i, 40, 30 );
		raytracer.CastRay( i, 800, 600,-3 );
        //raytracer.CastRay( i, 400, 300, -1);
		//}
        std::cout<<"frame "<<i<<"\n";
    }
#endif
    return EXIT_SUCCESS;
}
