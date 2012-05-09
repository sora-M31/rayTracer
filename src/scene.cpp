#include "scene.h"
#include "geometry.h"
#include "pointLight.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Scene::Scene()
{
    Shape* sphere = new Sphere( Vector( 1, 0, 10, 1), 1.0 );
    Material* diffuse = new Material ( 0, 0, sphere );
    sphere->SetMaterial( diffuse );

    Shape* plane = new Plane( Vector(0,1,0,0), -1, diffuse );

    m_shapes.push_back( plane );
    m_shapes.push_back( sphere );
    m_materials.push_back( diffuse );



    Light* light = new PointLight ( Vector (0,1,1,1), 10 );
    m_lights.push_back ( light);
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
