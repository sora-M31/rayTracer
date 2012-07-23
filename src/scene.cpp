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
Scene::Scene( const Camera& _camera )
:m_camera ( _camera )
{
    Shape* sphere1 = new Sphere( Vector( -2, 0.5, 0, 1), 1.0 );
    Shape* cube = new Mesh( Vector( 2, 0, -2, 1), "resources/cube.obj" );
    Shape* plane = new Mesh( Vector(0,0,0,1), "resources/plane.obj");
    Shape* teapot = new Mesh( Vector ( 0,0, 2, 1),"resources/teapotTexture.obj");
    Shape* sky = new Mesh( Vector ( 0,0, 0, 1),"resources/cubeSky.obj");
    Shape* cylinder = new Mesh( Vector ( -3,0, 3, 1),"resources/cylinder.obj");
    Shape* soccerball = new Mesh( Vector ( -3,0, 0, 1),"resources/soccerball.obj");

	//ka, kd, ks, km, kf, kg, index, attenuation, color, aniso
    Material* mirror = new Material ( 0, 0, 0, 1, 0, 0, 0, 0);
    Material* glossy = new Material ( 0, 0, 1, 0, 0, 1, 0, 0 ,Color(1,1,1,1),true);
    Material* diffuse = new Material ( 0, 0.8, 0.2, 0, 0, 0, 0, 0, Color(1,1,1,1) );
    Material* glass = new Material ( 0, 0, 0, 0, 1, 0, GLASS_INDEX,0 );
    Material* floor = new Material ( 0, 1, 0, 0 ,0, 0, 0, 0);

    //Image* checker = new Image(160, 160, Color(1,1,1,1) );
    //checker->MakeChecker();

    Image* salad = new Image( "resources/Wood.jpg" );
    floor->SetTexture( salad );

    sphere1->SetMaterial( diffuse );
    cube->SetMaterial( diffuse );
    teapot->SetMaterial( diffuse );
    plane->SetMaterial( floor );
    sky->SetMaterial( diffuse );
    cylinder->SetMaterial( diffuse );
    soccerball->SetMaterial( diffuse );

#if 1
	m_shapes.push_back( sky );
	m_shapes.push_back( plane );
    m_shapes.push_back( sphere1 );
    //m_shapes.push_back( cube );
    m_shapes.push_back( teapot);
    m_shapes.push_back( cylinder );
   // m_shapes.push_back( soccerball);
#endif
    m_materials.push_back( mirror );
    m_materials.push_back( floor );
    m_materials.push_back( glass );
    m_materials.push_back( glossy );
    m_materials.push_back( diffuse );
    //m_textures.push_back ( checker );
    m_textures.push_back ( salad );

    Light* areaKey = new AreaLight ( Vector (-2,3,-1,1), 3,3, Vector( 0,0,1,0), 5, 25, Color(1,0.3,0,1) );
    //Light* pointKey = new PointLight ( Vector (-1,4,-1,1), 200, Color(1,0.3,0,1) );
    Light* pointFill = new PointLight ( Vector (5,3,-1,1), 10, Color(0,0,1,1) );

    m_lights.push_back ( pointFill);
	//m_lights.push_back ( pointKey );
	m_lights.push_back ( areaKey );
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
//------------------------------------------------------------------------------
void Scene::Update( uint32_t _time)
{
	//m_camera.Translate( Vector( 0,5,-7,1) );
	m_camera.Translate( Vector( -1,3,-7,1) );
	m_camera.Rotate( -0.15, Vector(1,0,0,0 ));
	m_stack.push_back ( m_camera.LocalTransformation().Inverse() );
	m_stack.push_back ( Quaternion( 0.5*_time, Vector( 0,1,0,0 ) ).AsMatrix() );
#if 1
    uint32_t size = m_shapes.size();
    for( uint32_t i = 0; i < size; ++i )
    {
        //m_shapes[i]->Rotate( 0.05 * _time, Vector ( 0,1,0,0) );
		m_stack.push_back ( m_shapes[i]->LocalTransformation() );
		m_shapes[i]->ToCameraSpace( GetStackMatrix() );
		//m_stack.pop_back();
		m_stack.pop_back();
    }
    size = m_lights.size();
    for( uint32_t i = 0; i < size; ++i )
    {
        //m_lights[i]->Rotate( 0.05 * _time, Vector ( 0,1,0,0) );
        //m_lights[i]->Translate( Vector ( 0,0.5*_time,0,1) );
		m_stack.push_back ( m_lights[i]->LocalTransformation() );
		m_lights[i]->ToCameraSpace( GetStackMatrix() );
		m_stack.pop_back();
    }
#endif
	m_stack.pop_back();
	m_stack.pop_back();
}
//------------------------------------------------------------------------------
Matrix Scene::GetStackMatrix()
{
    std::list<Matrix>::iterator iter = m_stack.begin();
	Matrix transform;
	transform.AsIdentity();
    while( iter != m_stack.end() )
    {
        transform = transform * (*iter) ;
        //transform = (*iter) * transform ;
        ++iter;
    }
    return transform;
}
}//end of space
