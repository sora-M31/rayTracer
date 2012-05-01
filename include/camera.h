#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "matrix.h"
namespace rayTracer
{
class Camera
{
public:
    Camera();
    Camera ( const Matrix& _transform );
    ~Camera();

    Vector ToCameraSpace ( const Vector& _worldPosition );
    const Matrix& Transform() const { return m_transform; }
private:
    Matrix m_transform;
    Matrix m_worldToCamera;
};//end of class
}//end of namespace
#endif //end of define
