#include "raytracer.h"
#include "scene.h"
#include <math.h>
#include "image.h"
#include "vector2D.h"
int main()
{
#if 1
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
		if( i == 7 )
        raytracer.CastRay( i, 40, 30 );
    }
#endif
#if 0
	rayTracer::Texture texture;
	texture.LoadImage("resources/flower.jpg");
	rayTracer::Image img( texture.Width(), texture.Height() );
	for( uint32_t i=0; i< texture.Width() * texture.Height() ; ++i )
	{
		img[i]=texture[i];
	}
	img.WriteTga( "textureText" );
#endif

    return EXIT_SUCCESS;
}
