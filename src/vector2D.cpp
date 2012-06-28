#include "vector2D.h"
#include "util.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Vector2D::Vector2D()
{
    memset( m_data, '0', 2);
}
//------------------------------------------------------------------------------
Vector2D::~Vector2D()
{
}
//------------------------------------------------------------------------------
Vector2D::Vector2D( float _x, float _y )
{
     m_data[0] = _x;
     m_data[1] = _y;
}
//------------------------------------------------------------------------------
Vector2D::Vector2D( const Vector2D& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
}
//------------------------------------------------------------------------------
Vector2D Vector2D::Normalise() const
{
    float length = Length();
    assert( length != 0 );
    return Vector2D( m_data[0] / length, m_data[1] / length );
}
//------------------------------------------------------------------------------
Vector2D& Vector2D::operator = ( const Vector2D& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    return *this;
}
///------------------------------------------------------------------------------
Vector2D& Vector2D::operator += ( const Vector2D& _other )
{
    m_data[0] += _other.m_data[0];
    m_data[1] += _other.m_data[1];
    return *this;
}
//------------------------------------------------------------------------------
Vector2D& Vector2D::operator -= ( const Vector2D& _other )
{
    m_data[0] -= _other.m_data[0];
    m_data[1] -= _other.m_data[1];
    return *this;
}
//------------------------------------------------------------------------------
Vector2D& Vector2D::operator /= ( float _other )
{
    assert( _other != 0 );
    m_data[0] /= _other;
    m_data[1] /= _other;
    return *this;
}
//------------------------------------------------------------------------------
Vector2D operator *( float _leftHand, const Vector2D& _rightHand )
{
    return _rightHand * _leftHand;
}
//------------------------------------------------------------------------------
void Normalise( Vector2D& io_vector )
{
    io_vector = io_vector.Normalise();
}
//------------------------------------------------------------------------------
std::ostream& operator << ( std::ostream & _output, const Vector2D&  _VecToPrint )
{
    return _output << _VecToPrint.m_data[0]<< " "<< _VecToPrint.m_data[1]<<" ";
}
}
