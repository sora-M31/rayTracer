#include <fstream>
#include <sstream>
#include "rayTracer.h"
#include "util.h"
#include "vector.h"
#include "image.h"
#include "AABB.h"
#include "areaLight.h"
//#define TEST1
//#define EXPOSURE

namespace rayTracer
{
//------------------------------------------------------------------------------
RayTracer::RayTracer( Scene* _pScene, uint32_t _width, uint32_t _height )
:m_pScene( _pScene ),
 m_width( _width ),
 m_height( _height ),
 m_antialias( 0 ),
 m_depthOfField( 0 )
{
}
//------------------------------------------------------------------------------
void RayTracer::CreateRays()
{
	float pixelSize = 1.0 / (float) m_width ;
	float planeDis = m_pScene->GetCamera().ViewPlaneDis();

	for (uint32_t y = 0; y < m_height; ++y)
	{
		for (uint32_t x = 0; x < m_width; ++x)
		{
			Color color(0,0,0,0);

			float dx = ( x * pixelSize ) - 0.5f;
			float dy = ( y * pixelSize ) - 0.5f;

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
					m_rayList.push_back( Ray( Vector(0,0,0,1), Vector(dx+iter->u()*pixelSize, dy+iter->v()*pixelSize,planeDis, 1), g_air ) );
					++iter;
				}
			}
			else if( m_depthOfField )
			{
				std::vector<Vector>::const_iterator iter = m_pScene->GetCamera().LensSample().begin();
				while( iter != m_pScene->GetCamera().LensSample().end() )
				{
					Vector dir = m_pScene->GetCamera().RayDirection( dx, dy, *iter );
					m_rayList.push_back( Ray( (*iter), dir, g_air) );
					++iter;
				}
			}
			else
			{
				//Material::kAir
				m_rayList.push_back( Ray( Vector(0,0,0,1), Vector( dx, dy, planeDis, 0.0f ), g_air ) );
			}
		}
	}
}

//------------------------------------------------------------------------------
RayTracer::~RayTracer()
{}
//------------------------------------------------------------------------------
void RayTracer::CastRay( uint32_t _frame, float _exposure )
{
	Image img( m_width, m_height, Color(0,0,0,0) );
	int depth =3;
	std::ofstream debug_mel;
#ifdef TEST1
	debug_mel.open("output.mel");
#endif
	
	uint32_t raySize = m_rayList.size();
	uint32_t sampleSize(1);
	if( m_antialias )
	{
		sampleSize = m_antialias * m_antialias;
	}
	else if( m_depthOfField )
	{
		sampleSize = m_depthOfField * m_depthOfField;
	}
	for( uint32_t i=0; i< raySize; i+=sampleSize )
	{
		Color c(0,0,0,0);
		printf("% 3d%%", (int)(100*(float)i/(float)raySize) );
		for( uint32_t j=0; j<sampleSize; ++j )
		{
			c+= Trace( m_rayList[i + j], depth, debug_mel );
		}
		c/=(float)sampleSize;
		c.SetExposure( _exposure);
		img.Set( i/sampleSize , c );
		printf("\b\b\b\b");
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
	Intersection intersection = IntersectScene( _ray );
	if ( _depth < 0 )
		return c;

#if 0
	AABB test( 0,-2,3, 1, -1, 5 );
	float min, max;
	if( test.Intersect( _ray, min, max ) )
		c = Color ( min/15.0, 0,0,1);
#endif
#if 1
	if ( intersection.Intersected() )
	{
	#ifdef TEST1
		o_output<<"curve -p "
			   <<0<<" "
			   <<0<<" "
			   <<0<<" "
			   <<"-p "
			   <<intersection.Position().x()<<" "
			   <<intersection.Position().y()<<" "
			   <<intersection.Position().z()
			   <<";\n";
	#endif
#endif
#if 1
		c = Color( 0,0,0,1);
		const Material* pMaterial = intersection.GetMaterial();

		assert( pMaterial!=0 );
		uint32_t size = m_pScene->GetLights().size();

		if( pMaterial->ka() )
		{
			c+= AmbientOcc( intersection ) * pMaterial->ka();
		}
		if( pMaterial->kf() )
		{
			c += Fresnel( intersection, _ray, _depth, o_output ) * pMaterial->kf();
		}
		else if( pMaterial->km() - 0 > EPSILON )
		{
			Ray reflectRay( intersection.Position() + intersection.Normal() * EPSILON, MirrorReflection( intersection, _ray.Direction() ), intersection.GetMaterial() );
			c += Trace( reflectRay, --_depth, o_output ) ;
		}
		if( pMaterial->kg() )
		{
			c += GlossyReflection( intersection, _ray.Direction(), _depth, o_output ) * pMaterial->kg();
		}
		if( pMaterial->kd() || pMaterial->ks() || pMaterial->IsAnisotropic() )
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
					//loop the shadow ray
					Intersection shadowRayScene = IntersectScene( *iter );
					float nDotLight = intersection.Normal().Dot(iter->Direction() );
					if ( shadowRayScene.Distance() > *iter2)
					{
						//phong specular
						float specular = 0;
						if( pMaterial->ks() )
						{
							//antisotropical specular
							if( pMaterial->IsAnisotropic() )
							{
								specular += AnisotropicSpecular( intersection, _ray.Direction(), iter->Direction() ) * pMaterial->ks();
							}
							else
							{
								specular += Specular( intersection, _ray.Direction(), iter->Direction() ) * pMaterial->ks();
							}
						}
						Clamp(nDotLight, 0,1);
						//todo light and surface color
						shade += (intersection.GetColor() * light->GetColor() )* nDotLight * attenuation * pMaterial->kd()
								 + light->GetColor() * specular * nDotLight * attenuation ;
					}
					++iter;
					++iter2;
				}
				c += shade;
			}//end of light iteration
		}
	}//end of intersected
#endif
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
Intersection RayTracer::IntersectScene( const Ray& _ray )
{
	Intersection intersection;

	for (size_t i = 0; i < m_pScene->GetShapes().size(); ++i)
	{
		const Shape* shape = m_pScene->GetShapes()[i];
		Intersection tmpIntersection;
		if ( shape->Intersect( _ray, tmpIntersection)
             && tmpIntersection.Distance() < intersection.Distance()  )
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
	uint32_t e=10;
	SampleHemisphere( dirSamples, 6, e );
	float c(0);
	for( uint32_t i=0; i< dirSamples.size(); ++i )
	{
		Vector dir = u * dirSamples[i].x() + v *dirSamples[i].z() + w*dirSamples[i].y();
		Ray raySample( _intersection.Position() + _intersection.Normal() * EPSILON, dir, g_air );
		//if no intersection with objects in scene
		if( !IntersectScene( raySample ).Intersected() )
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
	float e = 100.0f;
	float reflectDotView = reflectDir.Dot( _viewingDir );
	Clamp( reflectDotView,0,1 );
	return pow( reflectDotView, e );
}
//------------------------------------------------------------------------------
float RayTracer::AnisotropicSpecular( const Intersection& _intersection, const Vector& _viewingDir, const Vector& _lightDir)
{
	Vector reflectDir = MirrorReflection( _intersection, _viewingDir );
	float alphaX = 0.7;
	float alphaY = 0.3;
	alphaX += EPSILON;
	alphaY += EPSILON;
	Vector halfVector = ( -_viewingDir.Normalise() + _lightDir.Normalise() ).Normalise();
	Vector normal = _intersection.Normal();
	float nDotHalf =  normal.Dot( halfVector ) ;
	float nDotLight =  normal.Dot( _lightDir );
	float nDotView =  normal.Dot( -_viewingDir );

	Clamp( nDotHalf, 0, 1);
	Clamp( nDotLight, 0, 1);
	Clamp( nDotView, 0, 1);

	Vector u,v;
	normal.GetBasis(u,v);

	float tmp1 = halfVector.Dot(u) /  alphaX ;
	float tmp2 = halfVector.Dot(v) / alphaY ;

	float p = 1.0 / ( 4.0 * PI * alphaX * alphaY * sqrt( nDotLight * nDotView) ) ;
	float beta = - 2.0 * ( tmp1 * tmp1 + tmp2 * tmp2 ) / (1.0 + nDotHalf );

	float specular = p * exp(beta);
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
#if 0
	float roulette = rand()/(float)RAND_MAX;
	if( roulette <= kr )
	{
#if 1
		//mirror
		Ray reflectRay( _intersection.Position() + _intersection.Normal(), MirrorReflection( _intersection, _ray.Direction() ), _intersection.GetMaterial() );
		c += Trace( reflectRay, --_depth, o_output ) ;
#endif
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
#endif
		Vector outRayDir;
		if( cosIn > 0)
		{
			outRayDir = _ray.Direction() * ratio + ( cosIn * ratio - cosOut ) * _intersection.Normal();
		}
		else
		{
			outRayDir = _ray.Direction() * ratio + ( cosOut - cosIn * ratio ) * _intersection.Normal();
		}
		Ray refractRay( _intersection.Position() - _intersection.Normal() * EPSILON,
						 outRayDir,
						 _intersection.GetMaterial() );
		Ray reflectRay( _intersection.Position() + _intersection.Normal(), MirrorReflection( _intersection, _ray.Direction() ), _intersection.GetMaterial() );
		Color shade(0,0,0,1);
		int depth = _depth -1;
		shade=Trace( refractRay, depth, o_output )*kt + Trace( reflectRay, depth, o_output )*kr ;
	return shade;
}
//------------------------------------------------------------------------------
Vector RayTracer::MirrorReflection( const Intersection& _intersection, const Vector& _inDir )
{
	return Vector( _inDir - 2.0f * ( _inDir.Dot( _intersection.Normal() ) * _intersection.Normal() ) );
}
//------------------------------------------------------------------------------
Color RayTracer::GlossyReflection( const Intersection& _intersection, const Vector& _viewingDir, int _depth, std::ofstream& o_output )
{
	//income radiance ray
	Vector reflectDir = MirrorReflection( _intersection, _viewingDir );
	Normalise( reflectDir );
	//reflect a sample of rays
	Vector w( reflectDir );
	Vector u,v;
	w.GetBasis( u, v );
	
	std::vector<Vector> dirSamples;
	uint32_t e=100;
	uint32_t sampleSize = 5;
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
		shade += Trace(raySample, --_depth, o_output )/ pow( tmp2, (int)e );
	}
	c += shade;
	return c;
}
}//end of namespace
