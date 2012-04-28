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
Vector::Vector ( float i_x, float i_y, float i_z, float i_w)
:m_x ( i_x ),
 m_y ( i_y ),
 m_z ( i_z ),
 m_w ( i_w )
{
}
//------------------------------------------------------------------------------
Vector::Vector ( const Vector& i_other )
: m_x ( i_other.m_x ),
  m_y ( i_other.m_y ),
  m_z ( i_other.m_z ),
  m_w ( i_other.m_w )
{
}
//------------------------------------------------------------------------------
Vector Vector::Normalise () const
{
    float length = Length ();
    assert ( length != 0 );
    return Vector ( m_x / length, m_y / length, m_z / length, m_w/ length );
}
//------------------------------------------------------------------------------
Vector& Vector::operator =  ( const Vector& i_other )
{
    m_x = i_other.m_x;
    m_y = i_other.m_y;
    m_z = i_other.m_z;
    m_w = i_other.m_w;
    return *this;
}
///------------------------------------------------------------------------------
Vector& Vector::operator +=  ( const Vector& i_other )
{
    m_x += i_other.m_x;
    m_y += i_other.m_y;
    m_z += i_other.m_z;
    m_w += i_other.m_w;
    return *this;
}
//------------------------------------------------------------------------------
Vector& Vector::operator -=  ( const Vector& i_other )
{
    m_x -= i_other.m_x;
    m_y -= i_other.m_y;
    m_z -= i_other.m_z;
    m_w -= i_other.m_w;
    return *this;
}
//------------------------------------------------------------------------------
Vector& Vector::operator /=  ( float i_other )
{
    assert ( i_other != 0 );
    m_x /= i_other;
    m_y /= i_other;
    m_z /= i_other;
    m_w /= i_other;
    return *this;
}
//------------------------------------------------------------------------------
bool Vector::operator ==  ( const Vector& i_other ) const
{
    if  ( RealEqual ( m_x, i_other.m_x )
         && RealEqual ( m_y, i_other.m_y )
         && RealEqual ( m_z, i_other.m_z )
         && RealEqual ( m_w, i_other.m_w ) )
        return true;
    else return false;
}
//------------------------------------------------------------------------------
Vector operator * ( float i_leftHand, const Vector& i_rightHand )
{
    return i_rightHand * i_leftHand;
}
//------------------------------------------------------------------------------
std::ostream& operator <<  ( std::ostream & i_output, const Vector&  i_VecToPrint )
{
    return i_output << i_VecToPrint.m_x<< " "<< i_VecToPrint.m_y<<" "<< i_VecToPrint.m_z<<" "<< i_VecToPrint.m_w;
}
}//end of namespace
