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
	//obj.ParseFile ("resources/teapotTexture.obj" );
	obj.ParseFile ("resources/cube.obj" );
    ObjLoader loadplane;
    loadplane.ParseFile( "resources/plane.obj");
    ObjLoader loadsky;
    loadsky.ParseFile( "resources/cubeSky.obj");
	//loadplane.PrintLoadedInfo();
	//loadplane.PrintSerializedInfo();
	ObjLoader scene;
	scene.ParseFile( "resources/cornellBox.obj" );

    Shape* sphere1 = new Sphere( Vector( 1, 0, 0, 1), 1.0 );
    Shape* sphere2 = new Sphere( Vector( -1, 2, 0, 1), 1.0 );
    Shape* plane = new Mesh( Vector(0,-0.9,0,1), loadplane );
    Shape* test = new Mesh( Vector ( -1,0, 2, 1), obj);
    Shape* sky = new Mesh( Vector ( 0,0, 5, 1), loadsky);
	Shape* cornellBox = new Mesh( Vector( 0,0,0,1), scene );

    Material* mirror = new Material ( 0, 0, 1 );
    Material* blueDiffuse = new Material ( 1, 0, 0 );
    Material* glass = new Material ( 0, 1, 0, GLASS_INDEX );
    Material* floor = new Material ( 1, 0, 0 );

    Texture* checker = new Texture(160, 160);
    checker->MakeChecker();
    floor->SetTexture( checker );
	blueDiffuse->SetColor( Color( 1,0,0,1 ));

    sphere1->SetMaterial( mirror );
    test->SetMaterial( blueDiffuse );
    sphere2->SetMaterial( blueDiffuse );
    plane->SetMaterial( floor );
    sky->SetMaterial( floor );
    sky->SetMaterial( mirror );
	//cornellBox->SetMaterial(  );

	m_shapes.push_back( sky );
	m_shapes.push_back( plane );
    m_shapes.push_back( sphere1 );
    //m_shapes.push_back( cornellBox );
    m_shapes.push_back( sphere2 );
    //m_shapes.push_back( test );
    m_materials.push_back( mirror );
    m_materials.push_back( floor );
    m_materials.push_back( glass );
    m_materials.push_back( blueDiffuse );
    m_textures.push_back ( checker );

    Light* light1 = new PointLight ( Vector (0,15,0,1), 200 );
    //Light* light2 = new AreaLight ( Vector (2,3,9,1),3,Vector(0,-1,0,0), 4, 4 );

    m_lights.push_back ( light1);
	//m_shapes.push_back ( light1);
	sky->GetMaterial()->GetColor(Vector2D(0,0)).PrintColor();
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
	m_camera.Translate( Vector( 0,5,-7,1) );
	m_camera.Rotate( -0.5, Vector(1,0,0,0 ));
#if 0
	std::cout<<m_camera.Transformation().Inverse()[0][3]<<" ";
	std::cout<<m_camera.Transformation().Inverse()[1][3]<<" ";
	std::cout<<m_camera.Transformation().Inverse()[2][3]<<"\n";
#endif
	m_stack.push_back ( m_camera.LocalTransformation().Inverse() );
	m_stack.push_back ( Quaternion( -0.5*_time, Vector( 0,1,0,0 ) ).AsMatrix() );
#if 1
    uint32_t size = m_shapes.size();
    for( uint32_t i = 0; i < size; ++i )
    {
#if 0
	std::cout<<m_shapes[i]->Transformation()[0][3]<<" ";
	std::cout<<m_shapes[i]->Transformation()[1][3]<<" ";
	std::cout<<m_shapes[i]->Transformation()[2][3]<<"\n";
#endif
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
