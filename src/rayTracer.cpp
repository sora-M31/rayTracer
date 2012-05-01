#include "rayTracer.h"
#include "util.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Material RayTracer::m_air = Material( 0, 1, 0,AIR_INDEX );
//------------------------------------------------------------------------------
RayTracer::RayTracer()
:m_antialias ( false ),
 m_depthOfField ( false ),
 m_softShadow ( false ),
 m_differentGeo ( false )
{}
//------------------------------------------------------------------------------
RayTracer::~RayTracer()
{}
//------------------------------------------------------------------------------
Intersection RayTracer::Intersect ( const Ray& _ray )
{
	Intersection intersection;

	for (size_t i = 0; i < m_scene.GetShapes().size(); ++i)
	{
		const Shape* shape = m_scene.GetShapes()[i];
		Intersection tmpIntersection;
		if ( shape->Intersect ( _ray, intersection )
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
	Intersection intersection = Intersect ( _ray );

	Color c(0,0,0,0);

	if ( _depth < 0 )
		return c;

#if _DEBUG
	o_output<<"curve -p "
		   <<_ray.Origin().x()<<" "
		   <<_ray.Origin().y()<<" "
		   <<_ray.Origin().z()<<" "
		   <<"-p "
		   <<_ray.Origin().x() + _ray.Direction().x()*10.0<<" "
		   <<_ray.Origin().y() + _ray.Direction().y()*10.0<<" "
		   <<_ray.Origin().z() + _ray.Direction().z()*10.0<<" "
		   <<";\n";
#endif

	if ( intersection.Intersected() )
	{
#if _DEBUG
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

		//if trace light directly reflected from light source
		if ( intersection.GetMaterial()->Reflection() < EPSILON &&
			 intersection.GetMaterial()->Refraction() < EPSILON )
		{
			//direct light
			uint32_t size = m_scene.GetLights().size();
			for ( uint32_t i= 0; i < size; ++i)
			{
				const Light* light = m_scene.GetLights()[i];
				std::list<Ray> shadowRays;
				float attenuation=1.0;
			    light->GetShadowRay(intersection, shadowRays, attenuation);
				std::list<Ray>::iterator iter = shadowRays.begin();
				//calculate shade from each light
				Color shade(0,0,0,0);
				while( iter != shadowRays.end() )
				{
					if( !Intersect ( *iter ).Intersected() )
					{
						shade +=  intersection.GetMaterial()->GetColor(intersection.Position() )
								* std::max(0.0f, intersection.Normal().Dot( (*iter).Direction()))
								* attenuation ;
					}
					++iter;
				}
				shade /= shadowRays.size();
				c+= shade;
			}
		}

		//else if trace reflected light
		if(intersection.GetMaterial()->Reflection() > EPSILON)
		{
			//reflected ray's direction
			Vector reflectDir = _ray.Direction()- 2.0 * _ray.Direction().Dot( intersection.Normal() ) * intersection.Normal();
			Ray reflectRay ( intersection.Position() + intersection.Normal() * EPSILON, reflectDir, &m_air);
			//color from reflected ray
			Color shade = Trace( reflectRay, --_depth, o_output);
			c += shade * intersection.GetMaterial()->Reflection();
		}

		//else if refractive
		if ( intersection.GetMaterial()->Refraction() > EPSILON)
		{
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
				c+=Trace ( refractRay, --_depth, o_output ) * intersection.GetMaterial()->Refraction();
			}
			else
			{
#if  _DEBUG
				std::cout<<" total refelction\n";
#endif
			}
		}
	}
#if _DEBUG
	else
	{
		o_output<<"curve -p "
			   <<_ray.Origin().x()<<" "
			   <<_ray.Origin().y()<<" "
			   <<_ray.Origin().z()<<" "
			   <<"-p "
			   <<_ray.Origin().x() + _ray.Direction().x()*100<<" "
			   <<_ray.Origin().y() + _ray.Direction().y()*100<<" "
			   <<_ray.Origin().z() + _ray.Direction().z()*100<<" "
			   <<";\n";
	}
#endif
	return c;
}
}//end of namespace
