#ifndef _SCENE_H_
#define _SCENE_H_

#include <vector>
#include "shape.h"
#include "light.h"
#include "camera.h"
namespace rayTracer
{
// --------------------------------------------------------------------------
/// \brief Scene class describes objects, lights and camera.
class Scene
{
public:
    Scene();
    ~Scene();
    void Update( uint32_t _time);
    const std::vector<Shape*>& GetShapes() const { return m_shapes; }
    const std::vector<Light*>& GetLights() const { return m_lights; }
	Matrix GetStackMatrix();
private:
    std::vector< Shape* > m_shapes;
    std::vector< Light* > m_lights;
    std::vector< Material* > m_materials;
    std::vector< Texture* > m_textures;
    Camera m_camera;
	std::list<Matrix> m_stack;
};//end of class
}//end of namespace
#endif //end of define
