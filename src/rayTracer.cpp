#include <fstream>
#include <sstream>
#include "rayTracer.h"
#include "util.h"
#include "vector.h"
#include "image.h"
#include "AABB.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
RayTracer::RayTracer( Scene* _pScene )
:m_pScene( _pScene ),
 m_antialias ( 0 ),
 m_depthOfField ( 0 )
{
}
//------------------------------------------------------------------------------
RayTracer::~RayTracer()
{}
//------------------------------------------------------------------------------
void RayTracer::CastRay( uint32_t _frame, uint32_t _width, uint32_t _height )
{
	Image img ( _width, _height );
	int depth =3;
	std::ofstream debug_mel;
//change name
#if 1
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
//------------------------------------------------------------------------------
Color RayTracer::Trace( const Ray& _ray, int _depth, std::ofstream& o_output )
{
	Color c(0,0,0,0);
	Intersection intersection = IntersectScene ( _ray );
	if ( _depth < 0 )
		return c;

	if ( intersection.Intersected() )
	{
						o_output<<"curve -p "
							   <<0<<" "
							   <<0<<" "
							   <<0<<" "
							   <<"-p "
							   <<intersection.Position().x()<<" "
							   <<intersection.Position().y()<<" "
							   <<intersection.Position().z()
							   <<";\n";
		c = Color ( 0,0,0,1);
		const Material* pMaterial = intersection.GetMaterial();

		assert( pMaterial!=0 );
		uint32_t size = m_pScene->GetLights().size();

		if( pMaterial->ka() )
		{
			c+= AmbientOcc( intersection ) * pMaterial->ka();
		}
		if( pMaterial->km() - 0 > EPSILON )
		{
			Ray reflectRay( intersection.Position() + intersection.Normal(), MirrorReflection( intersection, _ray.Direction() ), intersection.GetMaterial() );
			c += Trace( reflectRay, --_depth, o_output ) ;
		}
		if( pMaterial->kf() )
		{
			c += Fresnel( intersection, _ray, _depth, o_output ) * pMaterial->kf();
		}
		if( pMaterial->kg() )
		{
			c += GlossyReflection( intersection, _ray.Direction(), _depth, o_output ) * pMaterial->kg();
		}
		if( pMaterial->kd() )
		{
			//loop the light
			for ( uint32_t i= 0; i < size; ++i)
			{
				const Light* light = m_pScene->GetLights()[i];
				std::list<Ray> shadowRays;
				std::list<float> disList;
				float attenuation=1.0;
				light->GetShadowRay( intersection, shadowRays, disList, attenuation);
				//calculate shade from a single light
				std::list<Ray>::iterator iter = shadowRays.begin();
				std::list<float>::iterator iter2 = disList.begin();
				Color shade(0,0,0,1);
				while( iter != shadowRays.end() )
				{
#if 1
						o_output<<"curve -p "
							   <<iter->Origin().x()<<" "
							   <<iter->Origin().y()<<" "
							   <<iter->Origin().z()<<" "
							   <<"-p "
							   <<light->Position().x()<<" "
							   <<light->Position().y()<<" "
							   <<light->Position().z()
							   <<";\n";
#endif
					//loop the shadow ray
					float coefficient(0);
					Intersection shadowRayScene = IntersectScene( *iter );
					if ( shadowRayScene.RayParameter() > *iter2 )
					{
						//diffuse
						coefficient += pMaterial->kd();
						//phong specular
						if( pMaterial->ks() )
						{
							//antisotropical specular
							if( pMaterial->IsAnisotropic() )
							{
								coefficient += AnisotropicSpecular( intersection, _ray.Direction(), iter->Direction() ) * pMaterial->ks();
							}
							else
							{
								coefficient += Specular( intersection, _ray.Direction(), iter->Direction() ) * pMaterial->ks();
							}
						}
						float nDotLight = intersection.Normal().Dot(iter->Direction() );
						Clamp( nDotLight, 0, 1);
						shade = intersection.GetColor() *coefficient * nDotLight *  attenuation ;
					}
					++iter;
					++iter2;
				}
				if( shadowRays.size() > 1)
				{
					//shade /= light->Area();
				}
				c += shade;
			}//end of light iteration
		}
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
Color RayTracer::AmbientOcc( const Intersection& _intersection )
{
	//at intersection point, shoot rays into the hemisphere with samples given
	Vector w( _intersection.Normal() );
	Vector u,v;
	w.GetBasis( u, v );

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
			c+= dir.Dot( _intersection.Normal() );
		}
	}
	c/=dirSamples.size();
	return Color(c,c,c,1);
}
//------------------------------------------------------------------------------
float RayTracer::Specular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir )
{
	Vector reflectDir = MirrorReflection( _intersection, _lightDir );
	float e = 10.0f;
	float reflectDotView = reflectDir.Dot( _viewingDir );
	Clamp( reflectDotView,0,1 );
	return pow( reflectDotView, e );
}
//------------------------------------------------------------------------------
float RayTracer::AnisotropicSpecular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir)
{
	Vector reflectDir = MirrorReflection( _intersection, _viewingDir );
	float albedoS = 1;
	float alphaX = 0.8;
	float alphaY = 0.2;
	alphaX += EPSILON;
	alphaY += EPSILON;
	//Vector halfVector = ( -_viewingDir.Normalise() + reflectDir.Normalise() ).Normalise();
	Vector halfVector = ( -_viewingDir.Normalise() + _lightDir.Normalise() ).Normalise();
	Vector normal = _intersection.Normal();
	float nDotHalf =  normal.Dot( halfVector ) ;
	//float nDotLight =  normal.Dot( reflectDir );
	float nDotLight =  normal.Dot( _lightDir );
	float nDotView =  normal.Dot( -_viewingDir );

	//Clamp( nDotHalf, 0, 1);
	//Clamp( nDotLight, 0, 1);
	Clamp( nDotView, 0, 1);

	Vector u,v;
	normal.GetBasis(u,v);

	float tmp1 = halfVector.Dot(u) /  alphaX ;
	float tmp2 = halfVector.Dot(v) / alphaY ;

	float p = albedoS / ( 4.0 * PI * alphaX * alphaY * sqrt( nDotLight * nDotView) ) ;
	float beta = - 2.0 * ( tmp1 * tmp1 + tmp2 * tmp2 ) / (1.0 + nDotHalf );

	float specular = p * exp(beta);
	//c += MirrorReflection( _intersection, _viewingDir, _depth, o_output ) * ( albedoD/PI + specular) * nDotLight;
	//c +=  _intersection.GetColor() * (albedoD/PI + specular ) * nDotLight;
	return specular;
}
//------------------------------------------------------------------------------
Color RayTracer::Fresnel( const Intersection& _intersection, const Ray& _ray, int _depth, std::ofstream& o_output )
{
	float cosIn = _intersection.Normal().Dot( - _ray.Direction() );

	//sinIn/sinOut = outIndex/inIndex
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
	if( roulette <= kr )
	{
		//mirror
		Ray reflectRay( _intersection.Position() + _intersection.Normal(), MirrorReflection( _intersection, _ray.Direction() ), _intersection.GetMaterial() );
		c += Trace( reflectRay, _depth, o_output ) ;
	}
	else if( roulette <= kr + kt )
	{
#if 1
		//refraction
		Vector outRayDir;
		if( cosIn > 0)
		{
			outRayDir = _ray.Direction() * ratio + ( cosIn * ratio - cosOut ) * _intersection.Normal();
		}
		else
		{
			outRayDir = _ray.Direction() * ratio + ( cosOut - cosIn * ratio ) * _intersection.Normal();
		}
		Ray refractRay ( _intersection.Position() - _intersection.Normal() * EPSILON,
						 outRayDir,
						 _intersection.GetMaterial() );
		//todo beer's law
		//float distance = _intersection.RayParameter();
		//float attenuation =  expf( -distance * _ray->GetMaterial().Attenuation());
		c +=Trace ( refractRay, --_depth, o_output );
#endif
	}
	return c;
}
//------------------------------------------------------------------------------
Vector RayTracer::MirrorReflection( const Intersection& _intersection, const Vector& _inDir )
{
	return Vector( _inDir - 2.0f * ( _inDir.Dot( _intersection.Normal() ) * _intersection.Normal() ) );
}
//------------------------------------------------------------------------------
Color RayTracer::GlossyReflection( const Intersection& _intersection, const Vector& _viewingDir, int _depth, std::ofstream& o_output )
{
	#if 1
	//income radiance ray
	Vector reflectDir = MirrorReflection( _intersection, _viewingDir );
	Normalise( reflectDir );
	//reflect a sample of rays
	Vector w ( reflectDir );
	Vector u,v;
	w.GetBasis( u, v );
	
	std::vector<Vector> dirSamples;
	float e=100;
	uint32_t sampleSize = 25;
	SampleHemisphere( dirSamples, sampleSize, e );
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
		shade += Trace (raySample, --_depth, o_output ) /  pow( tmp2, e ) ;
	}
	c += shade / sampleSize;
	return c;
	#endif
}
}//end of namespace
