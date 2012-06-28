#ifndef _VECTOR2D_H_
#define _VECTOR2D_H_

#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <math.h>
//#include "util.h"

namespace rayTracer
{
class Vector2D
{
friend std::ostream& operator << ( std::ostream & _output, const Vector2D&  _VecToPrint );
friend Vector2D operator *( float _leftHand, const Vector2D& _rightHand );
friend void Normalise( Vector2D& io_vector );

public:
    Vector2D();
    ~Vector2D();
    Vector2D(float _u, float _v );
    Vector2D(const Vector2D& _other);
    // --------------------------------------------------------------------------
    /// \brief Get a new normalised vector
    /// \return Normalised vector
    Vector2D Normalise() const;
    float Dot(const Vector2D& _other) const;
    float Length() const;
    Vector2D operator + (const Vector2D& _other) const;
    Vector2D operator - (const Vector2D& _other) const;
    Vector2D operator - () const;
    Vector2D operator * ( float _other) const;
    Vector2D operator / ( float _other) const;
    Vector2D& operator = (const Vector2D& _other);
    Vector2D& operator += (const Vector2D& _other);
    Vector2D& operator -= (const Vector2D& _other);
    Vector2D& operator /= ( float _other);
    bool operator == ( const Vector2D& _other) const;
    float& operator [] ( uint32_t _index);
    const float& operator [] ( uint32_t _index) const;

    float& u() { return m_data[0]; }
    float& v() { return m_data[1]; }
    const float& u() const { return m_data[0]; }
    const float& v() const { return m_data[1]; }
private:
    float m_data[2];
};//end of class
//------------------------------------------------------------------------------
inline float Vector2D::Dot ( const Vector2D& _other ) const
{
    return   ( m_data[0] * _other.m_data[0] + m_data[1] * _other.m_data[1] );
}
//------------------------------------------------------------------------------
inline float Vector2D::Length () const
{
    float lenSqr = this->Dot ( *this ) ;
    //if( RealCompare( lenSqr, 0, 0.00000000000001) )
    if ( fabs( lenSqr - 0 ) < 0.00000000001 )
    {
        return 0;
    }
    return sqrt ( lenSqr );
}
//------------------------------------------------------------------------------
inline Vector2D Vector2D::operator +  ( const Vector2D& _other ) const
{
    return Vector2D ( m_data[0] + _other.m_data[0], m_data[1] + _other.m_data[1] );
}
//------------------------------------------------------------------------------
inline Vector2D Vector2D::operator *  ( float _other ) const
{
    return Vector2D ( m_data[0] *  _other, m_data[1] *  _other );
}
//------------------------------------------------------------------------------
inline Vector2D Vector2D::operator /  ( float _other ) const
{
    assert ( _other!=0 );
    return Vector2D ( m_data[0] / _other, m_data[1] / _other );
}
//------------------------------------------------------------------------------
inline Vector2D Vector2D::operator -  ( const Vector2D& _other ) const
{
    return Vector2D ( m_data[0] - _other.m_data[0], m_data[1] - _other.m_data[1] );
}
//------------------------------------------------------------------------------
inline Vector2D Vector2D::operator -  () const
{
    return Vector2D ( - m_data[0], -m_data[1] );
}
//------------------------------------------------------------------------------
inline float& Vector2D::operator [] ( uint32_t _index)
{
    assert ( _index < 2 );
    return m_data[_index];
}
//------------------------------------------------------------------------------
inline bool Vector2D::operator == ( const Vector2D& _other) const
{
    if ( fabs( m_data[0] - _other.m_data[0] ) < 0.00000000001
       && fabs( m_data[1] - _other.m_data[1] ) < 0.00000000001
    )
    return true;
    else return false;
}
//------------------------------------------------------------------------------
inline const float& Vector2D::operator [] ( uint32_t _index) const
{
    assert ( _index < 2 );
    return m_data[_index];
}
}//end of namespace
#endif //end of define
