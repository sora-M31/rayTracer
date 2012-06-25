#include "quaternion.h"
#include "util.h"


namespace rayTracer
{
//------------------------------------------------------------------------------
Quaternion::Quaternion()
{
    m_data[0] = 1;
    m_data[1] = 0;
    m_data[2] = 0;
    m_data[3] = 0;
}
//------------------------------------------------------------------------------
Quaternion::Quaternion(float _scalar, float _x, float _y, float _z)
{
    m_data[0] = _scalar;
    m_data[1] = _x;
    m_data[2] = _y;
    m_data[3] = _z;
}
//------------------------------------------------------------------------------
Quaternion::Quaternion(float _angle, const Vector& _axis)
{
    m_data[0] = cos(_angle/2.0);
    float halfsin = sin( _angle/2.0);
    m_data[1]= halfsin * _axis.x();
    m_data[2]= halfsin * _axis.y();
    m_data[3]= halfsin * _axis.z();
}
//------------------------------------------------------------------------------
Quaternion Quaternion::AsMultiplyIdentity()
{
    return Quaternion( 1,0,0,0);
}
//------------------------------------------------------------------------------
Quaternion Quaternion::Normalise() const
{

    float magnitude =sqrt( m_data[0] * m_data[0] +
                           m_data[1] * m_data[1] +
                           m_data[2] * m_data[2] +
                           m_data[3] * m_data[3] );

    assert( !RealCompare(magnitude, 0.0, 0.000000001) );
    float scalar = m_data[0]/magnitude;
    float x = m_data[1]/magnitude;
    float y = m_data[2]/magnitude;
    float z = m_data[3]/magnitude;
    return Quaternion( scalar, x, y, z );
}
//------------------------------------------------------------------------------
Matrix Quaternion::AsMatrix() const
{
    Quaternion tmp = Normalise();
    float xx = tmp.m_data[1]* tmp.m_data[1];
    float xy = tmp.m_data[1]* tmp.m_data[2];
    float xz = tmp.m_data[1]* tmp.m_data[3];
    float yz = tmp.m_data[2]* tmp.m_data[3];
    float yy = tmp.m_data[2]* tmp.m_data[2];
    float zz = tmp.m_data[3]* tmp.m_data[3];
    float wx = tmp.m_data[0]* tmp.m_data[1];
    float wy = tmp.m_data[0]* tmp.m_data[2];
    float wz = tmp.m_data[0]* tmp.m_data[3];

    return Matrix( 1.0-2.0*(yy+zz), 2.0 * (xy+wz),   2.0*(xz-wy),     0,
                   2.0*(xy-wz),     1.0-2.0*(xx+zz), 2.0*(yz+wx),     0,
                   2.0*(xz+wy),     2.0*(yz-wx),     1.0-2.0*(xx+yy), 0,
                   0,               0,               0,               1);
}
//------------------------------------------------------------------------------
Quaternion Quaternion::operator * (const Quaternion& _other) const
{
    float _scalar = _other.m_data[0];
    float _x = _other.m_data[1];
    float _y = _other.m_data[2];
    float _z = _other.m_data[3];

    float scalar = m_data[0]*_scalar - m_data[1]* _x     - m_data[2]*_y - m_data[3]*_z;
    float      x = m_data[0]*_x      + m_data[1]*_scalar + m_data[2]*_z - m_data[3]*_y;
    float      y = m_data[0]*_y      + m_data[2]*_scalar + m_data[3]*_x - m_data[1]*_z;
    float      z = m_data[0]*_z      + m_data[3]*_scalar + m_data[1]*_y - m_data[2]*_x;
    return Quaternion( scalar, x, y, z );
}
//------------------------------------------------------------------------------
Quaternion Quaternion::operator =  (const Quaternion& _other)
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    m_data[2] = _other.m_data[2];
    m_data[3] = _other.m_data[3];
    return *this;
}
//------------------------------------------------------------------------------
const float Quaternion::scalar() const
{
    return m_data[0];
}
//------------------------------------------------------------------------------
const float Quaternion::x() const
{
    return m_data[1];
}
//------------------------------------------------------------------------------
const float Quaternion::y() const
{
    return m_data[2];
}
//------------------------------------------------------------------------------
const float Quaternion::z() const
{
    return m_data[3];
}
}//end of namespace
