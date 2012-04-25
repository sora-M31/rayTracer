#include "vector.h"
#include <math.h>
#include <assert.h>

namespace rayTracer
{
//------------------------------------------------------------------------------
Vector::Vector ()
{
    memset ( m_data, '0', 3 );
}
//------------------------------------------------------------------------------
Vector::~Vector ()
{
    delete [] m_data;
}
//------------------------------------------------------------------------------
Vector::Vector ( float i_x, float i_y, float i_z )
:m_x ( i_x ),
 m_y ( i_y ),
 m_z ( i_z )
{
}
//------------------------------------------------------------------------------
Vector::Vector ( const Vector& i_other )
: m_x ( i_other.m_x ),
  m_y ( i_other.m_y ),
  m_z ( i_other.m_z )
{
}
//------------------------------------------------------------------------------
Vector Vector::Normalise () const
{
    float length = Length ();
    assert ( length != 0 );
    return Vector ( m_x / length, m_y / length, m_z / length );
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
                    m_x * i_other.m_y - m_y * i_other.m_x );
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
    return Vector ( m_x + i_other.m_x, m_y + i_other.m_y, m_z + i_other.m_z );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator *  ( const float i_other ) const
{
    return Vector ( m_x *  i_other, m_y *  i_other, m_z *  i_other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator /  ( const float i_other ) const
{
    assert ( i_other!=0 );
    return Vector ( m_x / i_other, m_y / i_other, m_z / i_other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator -  ( const Vector& i_other ) const
{
    return Vector ( ( m_x - i_other.m_x ), ( m_y - i_other.m_y ), ( m_z - i_other.m_z ) );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator -  () const
{
    return Vector ( - m_x, -m_y, -m_z );
}
//------------------------------------------------------------------------------
Vector& Vector::operator =  ( const Vector& i_other )
{
    m_x = i_other.m_x;
    m_y = i_other.m_y;
    m_z = i_other.m_z;
    return *this;
}
///------------------------------------------------------------------------------
Vector& Vector::operator +=  ( const Vector& i_other )
{
    m_x += i_other.m_x;
    m_y += i_other.m_y;
    m_z += i_other.m_z;
    return *this;
}
//------------------------------------------------------------------------------
Vector& Vector::operator -=  ( const Vector& i_other )
{
    m_x -= i_other.m_x;
    m_y -= i_other.m_y;
    m_z -= i_other.m_z;
    return *this;
}
//------------------------------------------------------------------------------
Vector& Vector::operator /=  ( const float i_other )
{
    assert ( i_other != 0 );
    m_x /= i_other;
    m_y /= i_other;
    m_z /= i_other;
    return *this;
}
//------------------------------------------------------------------------------
bool Vector::operator ==  ( const Vector& i_other ) const
{
    if  ( RealEqual ( m_x, i_other.m_x )
         && RealEqual ( m_y, i_other.m_y )
         && RealEqual ( m_z, i_other.m_z ) )
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
float Vector::GetValue ( uint32_t i_index )
{
    assert( i_index >= 0 && i_index < 3 );
    return m_data[ i_index ];
}
//------------------------------------------------------------------------------
void Vector::SetValue ( uint32_t i_index, float i_value )
{
    assert( i_index >= 0 && i_index < 3 );
    m_data[ i_index ] = i_value;
}
//------------------------------------------------------------------------------
inline Vector operator * ( float leftHand, const Vector& rightHand )
{
    return rightHand * leftHand;
}
//------------------------------------------------------------------------------
std::ostream& operator <<  ( std::ostream & i_output, const Vector&  i_VecToPrint )
{
    return i_output << " vector [ "<< i_VecToPrint.m_x<< " , "<< i_VecToPrint.m_y<<" , "<< i_VecToPrint.m_z<<" ] ";
}
}//end of namespace
