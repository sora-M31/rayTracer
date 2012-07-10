#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
int main()
{
    rayTracer::Scene scene;
    rayTracer::RayTracer raytracer ( &scene );
	//raytracer.SetDepthOfField();
	raytracer.SetAntialias();
    for(uint32_t i=0; i< 10; i +=1)
    {
        std::cout<<"frame "<<i<<"\n";
        scene.Update(i);
        // Cast rays into scene and write to image
        raytracer.CastRay( i, 400, 300 );
    }
#if 0
    //test square sample
    rayTracer::Image img( 256, 256 );
    ////img.Set( x, y, color );
    //std::vector<rayTracer::Vector2D> samples;
    //SampleSquare( samples );
#if 1
	using namespace rayTracer;
	std::vector<rayTracer::Vector> sampleshemi;
	SampleHemisphere(sampleshemi );
    for( size_t i =0; i< sampleshemi.size(); ++i )
    {
        //img.Set( (int)(samples[i].u()*256.0), (int)(samples[i].v() * 256.0), rayTracer::Color(1,1,1,1) );
        img.Set( (int)((sampleshemi[i].x()/2.0 + 0.5 )*256.0), (int)((sampleshemi[i].z()/2.0 + 0.5) * 256.0), rayTracer::Color(1,1,1,1) );
    }
#endif
	img.WriteTga( "sample.tga" );
#endif
    return EXIT_SUCCESS;
}
