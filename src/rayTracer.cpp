#include <fstream>
#include <sstream>
#include "rayTracer.h"
#include "util.h"
#include "vector.h"
#include "image.h"
#include "AABB.h"
#define TEST1


namespace rayTracer
{
//------------------------------------------------------------------------------
RayTracer::RayTracer( Scene* _pScene )
:m_pScene( _pScene ),
 m_antialias ( 0 ),
 m_depthOfField ( 0 )
{
}
#if 1
//------------------------------------------------------------------------------
Color RayTracer::AmbientOcc( const Intersection& _intersection )
{
	//at intersection point, shoot rays into the hemisphere with samples given
	Vector w(_intersection.Normal() );
	Vector tmp1, tmp2;
	w.ProjectAxis(tmp1,tmp2);
	Vector u = w.Cross(tmp1);
	Normalise( u );
	Vector v = w.Cross(u);
	Normalise( v );

	std::vector<Vector> dirSamples;
	float e=10;
	SampleHemisphere( dirSamples, 10, e );
	float c(0);
	for( uint32_t i=0; i< dirSamples.size(); ++i )
	{
		Vector dir = u * dirSamples[i].x() + v *dirSamples[i].z() + w*dirSamples[i].y();
		Ray raySample( _intersection.Position() + _intersection.Normal() * EPSILON, dir, g_air );
		//if no intersection with objects in scene
		if( !IntersectScene ( raySample ).Intersected() )
		{
			c+=1.0 * dir.Dot( _intersection.Normal() );
		}
	}
	c/=dirSamples.size();
	//average color by number of points
	return Color(c,c,c,0);
}
#endif
//------------------------------------------------------------------------------
Color RayTracer::Diffuse( const Intersection& _intersection, const Vector& _lightDir, float _attenuation )
{
	Color c = _intersection.GetColor() *
			  std::max( 0.0f, _intersection.Normal().Dot( _lightDir ) ) *
			  _attenuation;
	//c.PrintColor();
	return c;
}
//------------------------------------------------------------------------------
Color RayTracer::Specular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir, float _attenuation )
{
	//reflected direction
	Vector reflectDir = _lightDir - 2.0f * ( _lightDir.Dot( _intersection.Normal() ) * _intersection.Normal() );
	float e = 10.0f;
	Color c = _intersection.GetColor() *
			  std::max( 0.0f, _intersection.Normal().Dot( _lightDir ) )*
			  _attenuation *
			  pow( std::max( 0.0f, reflectDir.Dot( _viewingDir ) ), e );
	return c;
}
//------------------------------------------------------------------------------
Color RayTracer::Fresnel( const Intersection& _intersection, const Ray& _ray, int _depth, std::ofstream& o_output )
{
	float cosIn = _intersection.Normal().Dot( - _ray.Direction() );

	//sinIn/sinOut = outIndex/inIndex
	//std::cout<<_ray.GetMaterial()->Index() <<"/"<< _intersection.GetMaterial()->Index()<<"\n";
	float nIn = _ray.GetMaterial()->Index();
	float nOut = _intersection.GetMaterial()->Index();
	float ratio = nIn / nOut;
	float sinOutSquared = ( 1.0f- cosIn * cosIn ) * ratio * ratio;
	float cosOut = sqrt( 1.0f - sinOutSquared );
	float kr, kt;
	
	Color c(0,0,0,1);
	if ( sinOutSquared <= 1.0)
	{

		float nIncosIn = nIn * fabs(cosIn);
		float nOutcosOut = nOut * cosOut;
		float nIncosOut = nIn * cosOut;
		float nOutcosIn = nOut * fabs(cosIn);
		//s-polarised incident light reflection coefficient
		float rs = ( nIncosIn - nOutcosOut ) / ( nIncosIn + nOutcosOut );
		//p-polarised incident light reflection coefficient
		float ps = ( nIncosOut - nOutcosIn ) / ( nIncosOut + nOutcosIn );
		//reflection coefficient
		kr = ( rs*rs + ps*ps ) * 0.5;
		//transmission coefficient
		kt = 1.0 - kr;
	}
	else
	{
		kr = 1.0f;
		kt = 0.0;
		cosOut = 0.0;
	}
	float roulette = rand()/(float)RAND_MAX;
	//std::cout<<roulette<<"roulette\n";
	//std::cout<<kr<<"reflectance\n";
	//std::cout<<kt<<"transmission\n";
#if 1
	if( roulette <= kr )
	{
		//std::cout<<"reflection\n";
		c += MirrorReflection( _intersection, _ray.Direction(), _depth, o_output ) ;
	}
	else if( roulette <= kr + kt )
	{
#if 1
		Vector outRayDir;
		if( cosIn > 0)
		{
			outRayDir = _ray.Direction() * ratio + ( cosIn * ratio - cosOut ) * _intersection.Normal();
		}
		else
		{
			outRayDir = _ray.Direction() * ratio + ( cosOut - cosIn * ratio ) * _intersection.Normal();
		}
		Ray refractRay ( _intersection.Position() + outRayDir * EPSILON,
						 outRayDir,
						 _intersection.GetMaterial() );
		//todo beer's law
		//float distance = _intersection.RayParameter();
		//float attenuation =  expf( -distance * _ray->GetMaterial().Attenuation());
		c +=Trace ( refractRay, --_depth, o_output );
#endif
		c+= Color(0,0,0,1);
	}
#endif
		//c+=MirrorReflection( _intersection, _ray.Direction(), _depth, o_output );
		#if 0
		Vector outRayDir;
		if( cosIn > 0)
		{
			outRayDir = _ray.Direction() * ratio + ( cosIn * ratio - cosOut ) * _intersection.Normal();
		}
		else
		{
			outRayDir = _ray.Direction() * ratio + ( cosOut - cosIn * ratio ) * _intersection.Normal();
		}
		Ray refractRay ( _intersection.Position() + outRayDir * EPSILON,
						 outRayDir,
						 _intersection.GetMaterial() );

		//todo beer's law
		//float distance = _intersection.RayParameter();
		//float attenuation =  expf( -distance * _ray->GetMaterial().Attenuation());
		c +=Trace ( refractRay, --_depth, o_output );
		#endif
	return c;
}
//------------------------------------------------------------------------------
Color RayTracer::MirrorReflection( const Intersection& _intersection, const Vector& _viewingDir, int _depth, std::ofstream& o_output )
{
	//income radiance ray
	Vector reflectDir = _viewingDir - 2.0f * ( _viewingDir.Dot( _intersection.Normal() ) * _intersection.Normal() );
	Ray reflectRay ( _intersection.Position() + _intersection.Normal() * EPSILON, reflectDir, g_air);
	//color from income radiance
	Color c(0,0,0,1);
	Color shade =  Trace( reflectRay, --_depth, o_output);
	c += shade;
	return c;
}
//------------------------------------------------------------------------------
Color RayTracer::GlossyReflection( const Intersection& _intersection, const Vector& _viewingDir, int _depth, std::ofstream& o_output )
{
	//income radiance ray
	Vector reflectDir = _viewingDir - 2.0f * ( _viewingDir.Dot( _intersection.Normal() ) * _intersection.Normal() );
	Normalise( reflectDir );
#if 1
	//reflect a sample of rays
	Vector w ( reflectDir );
	Vector tmp1,tmp2;
	#if 0
	w.ProjectAxis(u,v);
	Normalise(u);
	Normalise(v);
	#endif
	w.ProjectAxis(tmp1,tmp2);
	Vector u = w.Cross(tmp1);
	Normalise( u );
	Vector v = w.Cross(u);
	Normalise( v );
	
	std::vector<Vector> dirSamples;
	float e=10;
	SampleHemisphere( dirSamples, 5, e );
	Color c(0,0,0,1);
	Color shade( 0,0,0,1);
	for( std::vector<Vector>::iterator iter = dirSamples.begin(); iter!= dirSamples.end(); ++iter )
	{
		Vector dir;
		if( iter->Dot(_intersection.Normal()) < 0 )
			dir = -u * iter->x() - v * iter->z() + w* iter->y();
		else
			dir = u * iter->x() + v * iter->z() + w* iter->y();
		Ray raySample( _intersection.Position() + _intersection.Normal() * EPSILON, dir, g_air );
		//radiance
		float tmp1 = _intersection.Normal().Dot( dir );
		float tmp2 = reflectDir.Dot( dir );
		Clamp(tmp1,0,1);
		Clamp(tmp2,0,1);
		shade += (Trace (raySample, --_depth, o_output ) * tmp1 * pow( tmp2, e ));
	}
	c += shade * 0.5;
#endif
	return c;
}
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
		if ( shape->Intersect ( _ray, tmpIntersection)
             && tmpIntersection.RayParameter() < intersection.RayParameter()  )
        {
			intersection = tmpIntersection;
        }
	}
	return intersection;
}
//------------------------------------------------------------------------------
Color RayTracer::Trace( const Ray& _ray, int _depth, std::ofstream& o_output )
{
//change name
#if TestAABB
	AABB test( Vector(-3,1,9,1), Vector(3,3,13,1) );
	if (test.Intersect( _ray,dis))
	{
		std::cout<<dis<<" ";
		return Color( 0.5/(dis-9),0,0,1);
	}
	else
		return Color ( 0,0,0,1);
}
#endif
	Intersection intersection = IntersectScene ( _ray );

	Color c(0,0,0,0);
	//std::cout<<_depth<<" depth\n";

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
		c = Color ( 0,0,0,1);

		assert( intersection.GetMaterial() !=0 );
		uint32_t size = m_pScene->GetLights().size();
		#if 0
		if( intersection.GetMaterial()->kRefraction() >0 )
		{
			c += Fresnel( intersection, _ray, _depth, o_output );
		}
		if( intersection.GetMaterial()->kGlossy() >0 )
		{
			c += GlossyReflection( intersection, _ray.Direction(), _depth, o_output );
		}
		if( intersection.GetMaterial()->kDiffuse() >0 )
		{
			for ( uint32_t i= 0; i < size; ++i)
			{
				const Light* light = m_pScene->GetLights()[i];
				std::list<Ray> shadowRays;
				float attenuation=1.0;
				light->GetShadowRay( intersection, shadowRays, attenuation);
				//calculate shade from a single light
				std::list<Ray>::iterator iter = shadowRays.begin();
				Color shade(0,0,0,1);
				while( iter != shadowRays.end() )
				{
					if ( !IntersectScene( *iter).Intersected() )
						shade += Diffuse( intersection, iter->Direction(), attenuation ) 
								 + Specular( intersection, _ray.Direction(), iter->Direction(), attenuation );
					++iter;
				}
				shade /= shadowRays.size();
				c += shade;// + ka * Ambient();
			}//end of light iteration
		}
		#endif
		c+= AmbientOcc( intersection );
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
//------------------------------------------------------------------------------
void RayTracer::CastRay( uint32_t _frame, uint32_t _width, uint32_t _height )
{
	Image img ( _width, _height );
	int depth =3;
	std::ofstream debug_mel;
//change name
#ifdef TEST1
	debug_mel.open("output.mel");
#endif

	// comment
	float pixelWidth = 1.0f / (float) img.Width();
	float pixelHeight = 1.0f / (float) img.Height();

	for (uint32_t y = 0; y < img.Height(); ++y)
	{
		for (uint32_t x = 0; x < img.Width(); ++x)
		{
			//std::cout<<"pixel "<<y<<" "<<x<<"\n";
			Color color(0,0,0,0);

			float dx = ( x * pixelWidth ) - 0.5f;
			float dy = ( y * pixelHeight ) - 0.5f;

			if( m_antialias )
			{
				//get samples
				std::vector< Vector2D > pixSamples(0);
				//sample pixels
				SampleSquare( pixSamples, m_antialias );
				//get color from samples and average them
				std::vector<Vector2D>::iterator iter = pixSamples.begin();
				Color shade(0,0,0,0);
				while( iter!= pixSamples.end() )
				{
					Ray cameraSpaceRay = Ray( Vector(0,0,0,1), Vector(dx+iter->u()*pixelWidth, dy+iter->v()*pixelHeight, 1, 1), g_air );
					color += Trace( cameraSpaceRay, depth, debug_mel);
					++iter;
				}
				color/=pixSamples.size();
			}
#if 1
			else if( m_depthOfField )
			{
				for( std::vector<Vector>::const_iterator iter = m_pScene->GetCamera().LensSample().begin();
					 iter != m_pScene->GetCamera().LensSample().end();
					 ++iter )
				{
					Vector dir = m_pScene->GetCamera().RayDirection( dx, dy, *iter );
					Ray cameraSpaceRay = Ray( (*iter), dir, g_air);
					color += Trace( cameraSpaceRay, depth, debug_mel);
				}
				color/= m_pScene->GetCamera().LensSample().size();
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
#ifdef TEST1
	debug_mel.close();
#endif
	char filename[256];
	sprintf(filename, "img/img%04d.tga", _frame+1 );
	img.WriteTga(filename  );
}
}//end of namespace
