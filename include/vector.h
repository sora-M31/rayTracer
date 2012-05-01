#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <math.h>

namespace rayTracer
{
class Vector
{
friend std::ostream& operator <<  ( std::ostream & _output, const Vector&  _VecToPrint );
friend Vector operator * ( float _leftHand, const Vector& _rightHand );
friend void Normalise ( Vector& io_vector );

public:
    Vector();
    ~Vector();
    Vector(float _x, float _y, float _z, float _w);
    Vector(const Vector& _other);
    // --------------------------------------------------------------------------
    /// \brief Get a new normalised vector
    /// \return Normalised vector
    Vector Normalise() const;
    float Dot(const Vector& _other) const;
    // --------------------------------------------------------------------------
    /// \brief 4D dot product
    /// \param _other
    /// \return 
    float Dot4(const Vector& _other) const;
    Vector Cross(const Vector& _other) const;
    float Length() const;
    uint8_t DominantAxis () const;
    Vector operator + (const Vector& _other) const;
    Vector operator - (const Vector& _other) const;
    Vector operator - () const;
    Vector operator * ( float _other) const;
    Vector operator / ( float _other) const;
    Vector& operator = (const Vector& _other);
    Vector& operator += (const Vector& _other);
    Vector& operator -= (const Vector& _other);
    Vector& operator /= ( float _other);
    float& operator [] ( uint32_t _index);
    const float& operator [] ( uint32_t _index) const;

    float& x() { return m_data[0]; }
    float& y() { return m_data[1]; }
    float& z() { return m_data[2]; }
    float& w() { return m_data[3]; }
    const float& x() const { return m_data[0]; }
    const float& y() const { return m_data[1]; }
    const float& z() const { return m_data[2]; }
    const float& w() const { return m_data[3]; }
private:
    float m_data[4];
};//end of class
//------------------------------------------------------------------------------
inline float Vector::Dot ( const Vector& _other ) const
{
    return   ( m_data[0] * _other.m_data[0] + m_data[1] * _other.m_data[1] + m_data[2] * _other.m_data[2] );
}
//------------------------------------------------------------------------------
inline float Vector::Dot4 ( const Vector& _other ) const
{
    return   ( m_data[0] * _other.m_data[0] + m_data[1] * _other.m_data[1] + m_data[2] * _other.m_data[2] + m_data[3] * _other.m_data[3] );
}
//------------------------------------------------------------------------------
inline Vector Vector::Cross ( const Vector& _other ) const
{
    return Vector ( m_data[1] * _other.m_data[2] - m_data[2] * _other.m_data[1],
                    m_data[2] * _other.m_data[0] - m_data[0] * _other.m_data[2],
                    m_data[0] * _other.m_data[1] - m_data[1] * _other.m_data[0],
                    0.0f );
}
//------------------------------------------------------------------------------
inline float Vector::Length () const
{
    float lenSqr = this->Dot ( *this ) ;
    assert ( lenSqr != 0 );
    return sqrt ( lenSqr );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator +  ( const Vector& _other ) const
{
    return Vector ( m_data[0] + _other.m_data[0], m_data[1] + _other.m_data[1], m_data[2] + _other.m_data[2], m_data[3] + _other.m_data[3] );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator *  ( float _other ) const
{
    return Vector ( m_data[0] *  _other, m_data[1] *  _other, m_data[2] *  _other, m_data[3] * _other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator /  ( float _other ) const
{
    assert ( _other!=0 );
    return Vector ( m_data[0] / _other, m_data[1] / _other, m_data[2] / _other, m_data[2] / _other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator -  ( const Vector& _other ) const
{
    return Vector ( m_data[0] - _other.m_data[0], m_data[1] - _other.m_data[1], m_data[2] - _other.m_data[2], m_data[3] - _other.m_data[3] );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator -  () const
{
    return Vector ( - m_data[0], -m_data[1], -m_data[2], m_data[3] );
}
//------------------------------------------------------------------------------
inline float& Vector::operator [] ( uint32_t _index)
{
    assert ( _index < 4 );
    return m_data[_index];
}
//------------------------------------------------------------------------------
inline const float& Vector::operator [] ( uint32_t _index) const
{
    assert ( _index < 4 );
    return m_data[_index];
}
}//end of namespace
#endif //end of define
