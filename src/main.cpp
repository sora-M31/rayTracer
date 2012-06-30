#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
int main()
{
    rayTracer::Scene scene;
    rayTracer::RayTracer raytracer ( &scene );
    for(float i=0; i< 0; i +=1)
    {
        std::cout<<"frame "<<i<<"\n";
        scene.Update(i);
        // Cast rays into scene and write to image
        raytracer.CastRay(i);
    }
    //test square sample
    rayTracer::Image img( 256, 256 );
    ////img.Set( x, y, color );
    std::vector<rayTracer::Vector2D> samples;
    SampleSquare( samples );
	#if 1
    for( size_t i =0; i< samples.size(); ++i )
    {
		std::cout<<i<<"coloring\n";
        img.Set( (int)(samples[i].u()*256.0), (int)(samples[i].v() * 256.0), rayTracer::Color(1,1,1,1) );
    }
#endif
	img.WriteTga( "sample.tga" );

    return EXIT_SUCCESS;
}
