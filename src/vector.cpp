#include "vector.h"
#include <math.h>
#include <assert.h>

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
inline float Vector::Dot ( const Vector& i_other ) const
{
    return   ( m_x * i_other.m_x + m_y * i_other.m_y + m_z * i_other.m_z );
}
//------------------------------------------------------------------------------
inline Vector Vector::Cross ( const Vector& i_other ) const
{
    return Vector ( m_y * i_other.m_z - m_z * i_other.m_y,
                    m_z * i_other.m_x - m_x * i_other.m_z,
                    m_x * i_other.m_y - m_y * i_other.m_x,
                    0.0f );
}
//------------------------------------------------------------------------------
float Vector::Length () const
{
    float lenSqr = this->Dot ( *this ) ;
    assert ( lenSqr != 0 );
    return sqrt ( lenSqr );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator +  ( const Vector& i_other ) const
{
    return Vector ( m_x + i_other.m_x, m_y + i_other.m_y, m_z + i_other.m_z, m_w + i_other.m_w );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator *  ( const float i_other ) const
{
    return Vector ( m_x *  i_other, m_y *  i_other, m_z *  i_other, m_w * i_other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator /  ( const float i_other ) const
{
    assert ( i_other!=0 );
    return Vector ( m_x / i_other, m_y / i_other, m_z / i_other, m_z / i_other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator -  ( const Vector& i_other ) const
{
    return Vector ( m_x - i_other.m_x, m_y - i_other.m_y, m_z - i_other.m_z, m_w - i_other.m_w );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator -  () const
{
    return Vector ( - m_x, -m_y, -m_z, m_w );
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
Vector& Vector::operator /=  ( const float i_other )
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
inline float Vector::GetX () const
{
    return m_x;
}
//------------------------------------------------------------------------------
inline float Vector::GetY () const
{
    return m_y;
}
//------------------------------------------------------------------------------
inline float Vector::GetZ () const
{
    return m_z;
}
//------------------------------------------------------------------------------
inline float Vector::GetW () const
{
    return m_w;
}
//------------------------------------------------------------------------------
inline void Vector::SetX ( float i_x )
{
    m_x = i_x;
}
//------------------------------------------------------------------------------
inline void Vector::SetY ( float i_y )
{
    m_y = i_y;
}
//------------------------------------------------------------------------------
void Vector::SetZ ( float i_z )
{
    m_z = i_z;
}
//------------------------------------------------------------------------------
float Vector::GetValue ( uint32_t i_index ) const
{
    assert( i_index >= 0 && i_index < 4 );
    return m_data[ i_index ];
}
//------------------------------------------------------------------------------
void Vector::SetValue ( uint32_t i_index, float i_value )
{
    assert( i_index >= 0 && i_index < 4 );
    m_data[ i_index ] = i_value;
}
//------------------------------------------------------------------------------
inline Vector operator * ( float i_leftHand, const Vector& i_rightHand )
{
    return i_rightHand * i_leftHand;
}
//------------------------------------------------------------------------------
std::ostream& operator <<  ( std::ostream & i_output, const Vector&  i_VecToPrint )
{
    return i_output << " vector [ "<< i_VecToPrint.m_x<< " , "<< i_VecToPrint.m_y<<" , "<< i_VecToPrint.m_z<<" , "<< i_VecToPrint.m_w<<" ] ";
}
}//end of namespace
