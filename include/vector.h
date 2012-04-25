#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <stdlib.h>
#include <iostream>
#include "util.h"

namespace rayTracer
{
class Vector
{
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
    /// \param _other Vector to copy from
    Vector(const Vector& _other);
    // --------------------------------------------------------------------------
    /// \brief Get a new normalised vector
    /// \return Normalised vector
    Vector Normalise() const;
    // --------------------------------------------------------------------------
    /// \brief Get dot product
    /// \param _other The othereter vector
    /// \return Dot product
    float Dot(const Vector& _other) const;
    // --------------------------------------------------------------------------
    /// \brief Get cross product
    /// \param _other
    /// \return Cross product
    Vector Cross(const Vector& _other) const;
    // --------------------------------------------------------------------------
    /// \brief Length of this vector
    /// \return The length
    float Length() const;
    // --------------------------------------------------------------------------
    /// \brief Operator + overload
    /// \param _other Parameter Vector
    /// \return Result vector
    Vector operator + (const Vector& _other) const;
    // --------------------------------------------------------------------------
    /// \brief Operator - overload
    /// \param _other othereter vector
    /// \return Result vector
    Vector operator - (const Vector& _other) const;
    // --------------------------------------------------------------------------
    /// \brief - overload, get negative value of this vector
    /// \return 
    Vector operator - () const;
    // --------------------------------------------------------------------------
    /// \brief Operator * overload, product of the vector and a float number
    /// \param _other othereter vector
    /// \return Product
    Vector operator * (const float _other) const;
    // --------------------------------------------------------------------------
    /// \brief Operator / overload, divide vector by a float number
    /// \param _other othereter number
    /// \return Result vector
    Vector operator / (const float _other) const;
    // --------------------------------------------------------------------------
    /// \brief Operator = overload
    /// \param _other Parameter vector
    /// \return This vector 
    Vector& operator = (const Vector& _other);
    // --------------------------------------------------------------------------
    /// \brief Operator += overload, assign the value of the sum of the othereter vector and this vector to this vector
    /// \param _other othereter vector
    /// \return This vector
    Vector& operator += (const Vector& _other);
    // --------------------------------------------------------------------------
    /// \brief Operator -= overload, assign cha of othereter vector and this vector to this vector
    /// \param _other othereter vector
    /// \return this vector
    Vector& operator -= (const Vector& _other);
    // --------------------------------------------------------------------------
    /// \brief Operator /= overload, assign divison of othereter by this vector to this vector 
    /// \param _other othereter 
    /// \return this vector
    Vector& operator /= (const float _other);
    // --------------------------------------------------------------------------
    /// \brief Operator == overload to get rid of floating point unprecisioness, Compare whether two vector are equal
    /// \param _other othereter vector
    /// \return Real if equal, false if not.
    bool operator == (const Vector& _other) const;
    float GetX() const;
    float GetY() const;
    float GetZ() const;
    float GetW() const;
    void SetX(float _x);
    void SetY(float _y);
    void SetZ(float _z);
    float GetValue ( uint32_t i_index ) const;
    void SetValue ( uint32_t i_index, float i_value );
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
}//end of namespace
#endif //end of define
