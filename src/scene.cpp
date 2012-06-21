#include "scene.h"
#include "geometry.h"
#include "pointLight.h"
#include "AreaLight.h"
#include "mesh.h"
#include "objLoader.h"
#include "kdTree.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Scene::Scene()
{
    ObjLoader obj;
    obj.ParseFile ("resources/teapot.obj" );
    //obj.PrintLoadedInfo();

    Shape* sphere1 = new Sphere( Vector( 1, 0, 10, 1), 1.0 );
    Shape* sphere2 = new Sphere( Vector( -1, 0, 7, 1), 1.0 );
    Shape* plane = new Plane( Vector(0,1,0,0), -1 );
    Shape* test = new Mesh( Vector ( 0.5,0, 8, 1), obj);

    Material* diffuse = new Material ( 0, 0, sphere1 );
    Material* test2 = new Material ( 0, 0 , test);
    //Material* glass = new Material ( 0, 1, test, GLASS_INDEX );
    Material* glass = new Material ( 0, 1, sphere2, GLASS_INDEX );
    Material* floor = new Material ( 0, 0, plane );

    Texture* checker = new Texture(160, 160);
    checker->MakeChecker();
    floor->SetTexture( checker );

    sphere1->SetMaterial( diffuse );
    //test->SetMaterial( glass );
    test->SetMaterial( test2 );
    sphere2->SetMaterial( glass );
    plane->SetMaterial( floor );

    m_shapes.push_back( plane );
    m_shapes.push_back( sphere1 );
    m_shapes.push_back( sphere2 );
    //m_shapes.push_back( test );
    m_materials.push_back( diffuse );
    m_materials.push_back( floor );
    m_materials.push_back( glass );
    m_materials.push_back( test2 );
    m_textures.push_back ( checker );

    Light* light1 = new PointLight ( Vector (1,2,1,1), 30 );
    //Light* light2 = new AreaLight ( Vector (2,3,9,1),3,Vector(0,-1,0,0), 4, 4 );

    m_lights.push_back ( light1);
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
