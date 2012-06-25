#ifndef _QUATERNION_H_
#define _QUATERNION_H_
#include "matrix.h"

namespace rayTracer
{
class Quaternion
{
    public:
        Quaternion();
        Quaternion(float _scalar, float _x, float _y, float _z);
        Quaternion(float _angle, const Vector& _axis);
        Quaternion AsMultiplyIdentity();
        Quaternion Normalise() const;
        Matrix AsMatrix() const;
        Quaternion operator * (const Quaternion& _other) const;
        Quaternion operator =  (const Quaternion& _other);
        const float scalar() const;
        const float x() const;
        const float y() const;
        const float z() const;
    private:
        float m_data[4];
};//end of class
}//end of namespace
#endif //end of define
