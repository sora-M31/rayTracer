#include "scene.h"
#include "geometry.h"
#include "pointLight.h"
#include "AreaLight.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Scene::Scene()
{
    Shape* sphere1 = new Sphere( Vector( 1, 0, 10, 1), 1.0 );
    Shape* sphere2 = new Sphere( Vector( -1, 0, 10, 1), 1.0 );

    Material* diffuse = new Material ( 0, 0, sphere1 );
    Material* glass = new Material ( 0.1, 0.9, sphere2, GLASS_INDEX );

    Shape* plane = new Plane( Vector(0,1,0,0), -1, diffuse );

    sphere1->SetMaterial( diffuse );
    sphere2->SetMaterial( glass );
    plane->SetMaterial( diffuse );

    m_shapes.push_back( plane );
    m_shapes.push_back( sphere1 );
    //m_shapes.push_back( sphere2 );
    m_materials.push_back( diffuse );

    //Light* light1 = new PointLight ( Vector (2,3,9,1), 20 );
    Light* light2 = new AreaLight ( Vector (0,1,0,1),3,Vector(0,-1,0,0), 4, 4 );

    m_lights.push_back ( light2);
}
//------------------------------------------------------------------------------
Scene::~Scene()
{
    uint32_t size = m_shapes.size();
    for( uint32_t i = 0; i < size; ++i )
    {
        delete m_shapes[i];
    }
    size = m_lights.size();
    for( uint32_t i = 0; i < size; ++i )
    {
        delete m_lights[i];
    }
    size = m_materials.size();
    for( uint32_t i = 0; i < size; ++i )
    {
        delete m_materials[i];
    }
    size = m_textures.size();
    for( uint32_t i = 0; i < size; ++i )
    {
        delete m_textures[i];
    }
}
}//end of space
