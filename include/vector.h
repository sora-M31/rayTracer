#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdlib.h>
#include <iostream>
#include <assert.h>
#include <math.h>
#include "util.h"

namespace rayTracer
{
class Vector
{
friend std::ostream& operator <<  ( std::ostream & i_output, const Vector&  i_VecToPrint );
public:
    // --------------------------------------------------------------------------
    /// \brief Default constructor
    Vector();
    // --------------------------------------------------------------------------
    /// \brief Default destructor
    ~Vector();
    // --------------------------------------------------------------------------
    /// \brief Constuctor
    /// \param _x x component
    /// \param _y y component
    /// \param _z z component
    Vector(float i_x, float i_y, float i_z, float i_w);
    // --------------------------------------------------------------------------
    /// \brief Copy constructor
    /// \param i_other Vector to copy from
    Vector(const Vector& i_other);
    // --------------------------------------------------------------------------
    /// \brief Get a new normalised vector
    /// \return Normalised vector
    Vector Normalise() const;
    // --------------------------------------------------------------------------
    /// \brief Get dot product
    /// \param i_other The othereter vector
    /// \return Dot product
    float Dot(const Vector& i_other) const;
    // --------------------------------------------------------------------------
    /// \brief For matrix
    /// \param i_other
    /// \return 
    float Dot4(const Vector& i_other) const;
    // --------------------------------------------------------------------------
    /// \brief Get cross product
    /// \param i_other
    /// \return Cross product
    Vector Cross(const Vector& i_other) const;
    // --------------------------------------------------------------------------
    /// \brief Length of this vector
    /// \return The length
    float Length() const;
    // --------------------------------------------------------------------------
    /// \brief Operator + overload
    /// \param i_other Parameter Vector
    /// \return Result vector
    Vector operator + (const Vector& i_other) const;
    // --------------------------------------------------------------------------
    /// \brief Operator - overload
    /// \param i_other othereter vector
    /// \return Result vector
    Vector operator - (const Vector& i_other) const;
    // --------------------------------------------------------------------------
    /// \brief - overload, get negative value of this vector
    /// \return 
    Vector operator - () const;
    // --------------------------------------------------------------------------
    /// \brief Operator * overload, product of the vector and a float number
    /// \param i_other othereter vector
    /// \return Product
    Vector operator * ( float i_other) const;
    // --------------------------------------------------------------------------
    /// \brief Operator / overload, divide vector by a float number
    /// \param i_other othereter number
    /// \return Result vector
    Vector operator / ( float i_other) const;
    // --------------------------------------------------------------------------
    /// \brief Operator = overload
    /// \param i_other Parameter vector
    /// \return This vector 
    Vector& operator = (const Vector& i_other);
    // --------------------------------------------------------------------------
    /// \brief Operator += overload, assign the value of the sum of the othereter vector and this vector to this vector
    /// \param i_other othereter vector
    /// \return This vector
    Vector& operator += (const Vector& i_other);
    // --------------------------------------------------------------------------
    /// \brief Operator -= overload, assign cha of othereter vector and this vector to this vector
    /// \param i_other othereter vector
    /// \return this vector
    Vector& operator -= (const Vector& i_other);
    // --------------------------------------------------------------------------
    /// \brief Operator /= overload, assign divison of othereter by this vector to this vector 
    /// \param i_other othereter 
    /// \return this vector
    Vector& operator /= ( float i_other);
    // --------------------------------------------------------------------------
    /// \brief Operator == overload to get rid of floating point unprecisioness, Compare whether two vector are equal
    /// \param i_other othereter vector
    /// \return Real if equal, false if not.
    bool operator == (const Vector& i_other) const;
    float& operator [] ( uint32_t i_index);
    const float& operator [] ( uint32_t i_index) const;
private:
    union
    {
        float m_data[4];
        struct{
                float m_x;
                float m_y;
                float m_z;
                float m_w;
              };
    };
};//end of class
//------------------------------------------------------------------------------
inline float Vector::Dot ( const Vector& i_other ) const
{
    return   ( m_x * i_other.m_x + m_y * i_other.m_y + m_z * i_other.m_z );
}
//------------------------------------------------------------------------------
inline float Vector::Dot4 ( const Vector& i_other ) const
{
    return   ( m_x * i_other.m_x + m_y * i_other.m_y + m_z * i_other.m_z + m_w * i_other.m_w );
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
inline float Vector::Length () const
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
inline Vector Vector::operator *  ( float i_other ) const
{
    return Vector ( m_x *  i_other, m_y *  i_other, m_z *  i_other, m_w * i_other );
}
//------------------------------------------------------------------------------
inline Vector Vector::operator /  ( float i_other ) const
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
inline float& Vector::operator [] ( uint32_t i_index)
{
    assert ( i_index < 4 );
    return m_data[ i_index ];
}
//------------------------------------------------------------------------------
inline const float& Vector::operator [] ( uint32_t i_index) const
{
    assert ( i_index < 4 );
    return m_data[ i_index ];
}
}//end of namespace
#endif //end of define
