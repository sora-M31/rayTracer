#include "vector.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
Vector::Vector ()
{
    memset ( m_data, '0', 4);
}
//------------------------------------------------------------------------------
Vector::~Vector ()
{
}
//------------------------------------------------------------------------------
Vector::Vector ( float _x, float _y, float _z, float _w)
{
     m_data[0] = _x;
     m_data[1] = _y;
     m_data[2] = _z;
     m_data[3] = _w;
}
//------------------------------------------------------------------------------
Vector::Vector ( const Vector& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    m_data[2] = _other.m_data[2];
    m_data[3] = _other.m_data[3];
}
//------------------------------------------------------------------------------
Vector Vector::Normalise () const
{
    float length = Length ();
    assert ( length != 0 );
    return Vector ( m_data[0] / length, m_data[1] / length, m_data[2] / length, m_data[3] / length );
}
//------------------------------------------------------------------------------
Vector& Vector::operator =  ( const Vector& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    m_data[2] = _other.m_data[2];
    m_data[3] = _other.m_data[3];
    return *this;
}
///------------------------------------------------------------------------------
Vector& Vector::operator +=  ( const Vector& _other )
{
    m_data[0] += _other.m_data[0];
    m_data[1] += _other.m_data[1];
    m_data[2] += _other.m_data[2];
    m_data[3] += _other.m_data[3];
    return *this;
}
//------------------------------------------------------------------------------
Vector& Vector::operator -=  ( const Vector& _other )
{
    m_data[0] -= _other.m_data[0];
    m_data[1] -= _other.m_data[1];
    m_data[2] -= _other.m_data[2];
    m_data[3] -= _other.m_data[3];
    return *this;
}
//------------------------------------------------------------------------------
Vector& Vector::operator /=  ( float _other )
{
    assert ( _other != 0 );
    m_data[0] /= _other;
    m_data[1] /= _other;
    m_data[2] /= _other;
    m_data[3] /= _other;
    return *this;
}
//------------------------------------------------------------------------------
bool Vector::operator ==  ( const Vector& _other ) const
{
    if  ( RealEqual ( m_data[0], _other.m_data[0] )
         && RealEqual ( m_data[1], _other.m_data[1] )
         && RealEqual ( m_data[2], _other.m_data[2] )
         && RealEqual ( m_data[3], _other.m_data[3] ) )
        return true;
    else return false;
}
//------------------------------------------------------------------------------
Vector operator * ( float _leftHand, const Vector& _rightHand )
{
    return _rightHand * _leftHand;
}
//------------------------------------------------------------------------------
void Normalise ( Vector& io_vector )
{
    io_vector = io_vector.Normalise();
}
//------------------------------------------------------------------------------
std::ostream& operator <<  ( std::ostream & _output, const Vector&  _VecToPrint )
{
    return _output << _VecToPrint.m_data[0]<< " "<< _VecToPrint.m_data[1]<<" "<< _VecToPrint.m_data[2]<<" "<< _VecToPrint.m_data[3];
}
}//end of namespace
