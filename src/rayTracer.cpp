#include <fstream>
#include <sstream>
#include "rayTracer.h"
#include "util.h"
#include "vector.h"
#include "image.h"
#include "AABB.h"
#define TEST


namespace rayTracer
{
//------------------------------------------------------------------------------
RayTracer::RayTracer( Scene* _pScene )
:m_pScene( _pScene ),
 m_antialias ( false ),
 m_depthOfField ( false ),
 m_softShadow ( false ),
 m_differentGeo ( false )
{
#if 0
	if(m_depthOfField)
	{
		//sampling camera
		//set aperture and focal depth
		float aperture = 1;
		//sample lens
		float unitNumber = 8;
		
		Vector unitX = Vector(1,0,0,0);
		Vector unitY = Vector(0,1,0,0);
		Vector centre = Vector(0,0,0,1);

		Sampling( centre, aperture, aperture, unitNumber, unitNumber, unitX, unitY, lenSample );
	}
#endif
}
#if 0
//------------------------------------------------------------------------------
Color RayTracer::AmbientOcc( const Intersection& _intersection)
{
	float c=0;
	//at intersection point, shoot rays into the hemisphere with samples given
	shadowRays;
	//loop through all the ray
	for( std::vector<Ray>::iterator iter = shadowRays.begin(); iter != shadowRays.end(); ++iter )
	{
		//if no intersection with objects in scene
		// c += 1
	}
	//average color by number of points
	return Color( c, c, c, 1 );
}
#endif
//------------------------------------------------------------------------------
Color RayTracer::Diffuse( const Intersection& _intersection, const Vector& _lightDir, float _attenuation )
{
	Color c = _intersection.GetColor() *
			  std::max( 0.0f, _intersection.Normal().Dot( _lightDir ) ) *
			  _attenuation;
	return c;
}
//------------------------------------------------------------------------------
Color RayTracer::Specular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir, float _attenuation )
{
	//reflected direction
	Vector reflectDir = _lightDir - 2.0f * ( _lightDir.Dot( _intersection.Normal() ) * _intersection.Normal() );
	//
	float e = 10.0f;
	Color c = _intersection.GetColor() *
			  std::max( 0.0f, _intersection.Normal().Dot( _lightDir ) )*
			  _attenuation *
			  pow( std::max( 0.0f, reflectDir.Dot( _viewingDir ) ), e );
	return c;
}
//------------------------------------------------------------------------------
#if 0
Color RayTracer::Refract()
{
			//else if refractive
			if ( intersection.GetMaterial()->Refraction() > EPSILON)
			{
				//comment?
				//refraction
				Vector reverseNormal = -intersection.Normal();
				float cosIn = reverseNormal.Dot( _ray.Direction()) ;
				//cosSquared+sinSquared = 1
				//cosIn/cosOut = outIndex/inIndex
				float ratio = _ray.GetMaterial()->Index() / intersection.GetMaterial()->Index();
				float sinOutSquared = ( 1.0f- cosIn * cosIn ) * ratio * ratio;
				if ( sinOutSquared < 1.0)
				{
					Vector outRayDir = _ray.Direction() * ratio - ( cosIn * ratio + sqrtf( 1.0 - sinOutSquared) ) * intersection.Normal();
					Ray refractRay ( intersection.Position() + outRayDir * EPSILON,
									 outRayDir,
									 intersection.GetMaterial() );

					//float distance = intersection.RayParameter();
					//float attenuation =  expf( -distance * _ray->GetMaterial().Attenuation()); 
					c +=Trace ( refractRay, --_depth, o_output ) * intersection.GetMaterial()->Refraction();
				}
				else
				{
#if  _DEBUG
					std::cout<<" total refelction\n";
#endif
				}
			}
}
#endif
#if  1
Color RayTracer::MirrorReflection( const Intersection& _intersection, const Vector& _viewingDir, uint32_t _depth, std::ofstream& o_output )
{
	Color c(0,0,0,1);
	//income radiance direction
	Vector reflectDir = _viewingDir - 2.0f * ( _viewingDir.Dot( _intersection.Normal() ) * _intersection.Normal() );

	Ray reflectRay ( _intersection.Position() + _intersection.Normal() * EPSILON, reflectDir, g_air);
	//color from reflected ray
	//std::cout<<_depth<<"callling depth\n";
	Color shade = Trace( reflectRay, _depth--, o_output);
	c += shade;
	return c;
}
#endif
//------------------------------------------------------------------------------
RayTracer::~RayTracer()
{}
//------------------------------------------------------------------------------
Intersection RayTracer::IntersectScene ( const Ray& _ray )
{
	Intersection intersection;

	for (size_t i = 0; i < m_pScene->GetShapes().size(); ++i)
	{
		const Shape* shape = m_pScene->GetShapes()[i];
		Intersection tmpIntersection;
		if ( shape->Intersect ( _ray, intersection)
             && tmpIntersection.RayParameter() < intersection.RayParameter()  )
        {
			intersection = tmpIntersection;
        }
	}
	return intersection;
}
//------------------------------------------------------------------------------
Color RayTracer::Trace( const Ray& _ray, uint32_t _depth, std::ofstream& o_output )
{
//change name
//std::cout<<_depth<<" depth input\n";
#if TestAABB
	AABB test( Vector(-3,1,9,1), Vector(3,3,13,1) );
	float dis;
	if (test.Intersect( _ray,dis))
	{
		std::cout<<dis<<" ";
		return Color( 0.5/(dis-9),0,0,1);
	}
	else
		return Color ( 0,0,0,1);
}
#endif
#if 1
	Intersection intersection = IntersectScene ( _ray );

	Color c(0,0,0,0);

	//rescursion depth limit
	if ( _depth < 0 )
		return c;

	if ( intersection.Intersected() )
	{
#ifdef TEST1
		o_output<<"curve -p "
			   <<_ray.Origin().x()<<" "
			   <<_ray.Origin().y()<<" "
			   <<_ray.Origin().z()<<" "
			   <<"-p "
			   <<intersection.Position().x()<<" "
			   <<intersection.Position().y()<<" "
			   <<intersection.Position().z()<<" "
			   <<";\n";
#endif
		c.a() = 1.0f;
		uint32_t size = m_pScene->GetLights().size();
		for ( uint32_t i= 0; i < size; ++i)
		{
			const Light* light = m_pScene->GetLights()[i];
			std::list<Ray> shadowRays;
			float attenuation=1.0;
			light->GetShadowRay( intersection, shadowRays, attenuation);

#ifdef TEST
			RayList::iterator test = shadowRays.begin();
			while( test != shadowRays.end() )
			{
				o_output<<"curve -p "
				   <<(*test).Origin().x()<<" "
				   <<(*test).Origin().y()<<" "
				   <<(*test).Origin().z()<<" "
				   <<"-p "
				   <<(*test).Origin().x() + (*test).Direction().x()*100<<" "
				   <<(*test).Origin().y() + (*test).Direction().y()*100<<" "
				   <<(*test).Origin().z() + (*test).Direction().z()*100<<" "
				   <<";\n";
				++test;
			}
#endif
			//std::cout<<_depth<<" depth \n";

			//calculate shade from a single light
			std::list<Ray>::iterator iter = shadowRays.begin();
			Color shade(0,0,0,0);
			assert( intersection.GetMaterial() !=0 );
			while( iter != shadowRays.end() )
			{
				if ( IntersectScene( *iter).Intersected() )
				{
					if ( intersection.GetMaterial()->kMirror() > EPSILON )
						shade += MirrorReflection( intersection, _ray.Direction(), _depth, o_output) * (intersection.GetMaterial()->kMirror() );
				}
				else
				{
					if ( intersection.GetMaterial()->kMirror() < EPSILON )
						shade += Diffuse( intersection, iter->Direction(), attenuation ) * ( intersection.GetMaterial()->kDiffuse() ) +
							 Specular( intersection, _ray.Direction(), iter->Direction(), attenuation ) * ( intersection.GetMaterial()->kSpecular() );

				}
				++iter;
			}
			shade /= shadowRays.size();
			c += shade;// + ka * Ambient();
		}//end of light iteration
	}//end of intersected
#ifdef TEST1
	else
	{
		//not intersected
		o_output<<"curve -p "
			   <<_ray.Origin().x()<<" "
			   <<_ray.Origin().y()<<" "
			   <<_ray.Origin().z()<<" "
			   <<"-p "
			   <<_ray.Origin().x() + _ray.Direction().x()*50<<" "
			   <<_ray.Origin().y() + _ray.Direction().y()*50<<" "
			   <<_ray.Origin().z() + _ray.Direction().z()*50
			   <<";\n";
	}
#endif
	return c;
}
#endif
//------------------------------------------------------------------------------
void RayTracer::CastRay( uint32_t _frame)
{
	Image img (800, 600);
	uint32_t depth =3;
	std::ofstream debug_mel;
//change name
#ifdef TEST
	debug_mel.open("output.mel");
#endif

	// comment
	float pixelWidth = 1.0f / (float) img.Width();
	float pixelHeight = 1.0f / (float) img.Height();

	for (uint32_t y = 0; y < img.Height(); ++y)
	{
		for (uint32_t x = 0; x < img.Width(); ++x)
		{
			Color color(0,0,0,0);

			float dx = ( x * pixelWidth ) - 0.5f;
			float dy = ( y * pixelHeight ) - 0.5f;

			if( m_antialias )
			{
				//get samples
				std::list< Vector > pixSamples(0);
				//change lines
				//sample pixels
				Sampling( Vector( dx, dy, 1.0f, 0.0f ), pixelWidth, pixelHeight, 4, 4,
								  Vector( 1,0,0,0 ), Vector( 0,1,0,0 ), pixSamples );

				//get color from samples and average them
				std::list<Vector>::iterator iter = pixSamples.begin();
				while( iter!= pixSamples.end() )
				{
					Ray cameraSpaceRay = Ray( Vector(0,0,0,1), (*iter), g_air );
					color += Trace( cameraSpaceRay, depth, debug_mel);
					++iter;
				}
				color/=pixSamples.size();
			}
			//depth of field
#if 0
			else if( m_depthOfField )
			{
				//point on ray = origin + dir * param
				float focalLength = 10;
				Vector focalPoint = Vector(0, 0, 0, 1.0f) + Vector(dx, dy, 1.0f, 0) * focalLength;
				//calculate color using rays formed from sample points on lens and fp on focal plane,
				std::list<Vector>::const_iterator iter = m_pCamera->LensSample().begin();
				while( iter!= m_pCamera->LensSample().end() )
				{
					Vector dir = (focalPoint - (*iter) ).Normalise();
					Ray cameraSpaceRay = Ray( (*iter), dir, g_air);
					Ray ray = m_pCamera->Transformation() * cameraSpaceRay;
					color += Trace( ray, depth, debug_mel);
					++iter;
				}
				color/= m_pCamera->LensSample().size();
			}
#endif
#if 0
			else if( m_depthOfField )
			{
				std::list<Vector>::const_iterator iter = m_pCamera->LensSample().begin();
				while( iter!= m_pCamera->LensSample().end() )
				{
					Vector dir = m_pCamera->RayDirection( dx, dy, *iter );
					Ray cameraSpaceRay = Ray( (*iter), dir, g_air);
					Ray ray = m_pCamera->Transformation() * cameraSpaceRay;
					//Ray ray = _camTrans * cameraSpaceRay;
					color += Trace( ray, depth, debug_mel);
					++iter;
				}
				color/= m_pCamera->LensSample().size();
			}
#endif
			else
			{
				//Material::kAir
				Ray cameraSpaceRay = Ray( Vector(0,0,0,1), Vector( dx, dy, 1.0f, 0.0f ), g_air );
				color = Trace( cameraSpaceRay, depth, debug_mel);
			}

			img.Set( x, y, color );
		}
	}
#ifdef TEST
	debug_mel.close();
#endif
	char filename[256];
	sprintf(filename, "img/img%04d.tga", _frame+1 );
	// Format the filename
#if 0
	std::stringstream ss;
	ss << "img/img";
	ss.width( 4 );
	ss.fill( '0' );
	ss << _frame +1 << ".tga";
	// Write the image to file
	img.WriteTga( ss.str().c_str() );
#endif 
	img.WriteTga(filename  );
}
}//end of namespace
