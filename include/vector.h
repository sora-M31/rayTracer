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
    Vector(float _x, float _y, float _z);
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
    // --------------------------------------------------------------------------
    /// \brief Accestor, get x component value
    /// \return Value of m_x
    float GetX() const;
    // --------------------------------------------------------------------------
    /// \brief Accestor, get y component value
    /// \return Value of m_y
    float GetY() const;
    // --------------------------------------------------------------------------
    /// \brief Accestor, get z component value
    /// \return Value of m_z
    float GetZ() const;
    // --------------------------------------------------------------------------
    /// \brief Set value of x to passed in value
    /// \param _x Value to be set
    void SetX(float _x);
    // --------------------------------------------------------------------------
    /// \brief Set value of y to passed in value
    /// \param _y Value to be set
    void SetY(float _y);
    // --------------------------------------------------------------------------
    /// \brief Set value of z to passed in value
    /// \param _z Value to be set
    void SetZ(float _z);
    // --------------------------------------------------------------------------
    /// \brief Get the value of the name with the index given
    /// \param 
    /// \param i_value
    /// \return 
    float GetValue ( uint32_t i_index );
    // --------------------------------------------------------------------------
    /// \brief set the no index to value given
    /// \param i_index
    /// \param i_value
    void SetValue ( uint32_t i_index, float i_value );
private:
    union
    {
        float m_data[3];
        struct{
                float m_x;
                float m_y;
                float m_z;
              };
    };
};//end of class
}//end of namespace
#endif //end of define
