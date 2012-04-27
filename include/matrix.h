#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string.h>
#include <vector.h>

namespace rayTracer
{
class Matrix
{
public:
    // --------------------------------------------------------------------------
    /// \brief Constructor
    Matrix();
    // --------------------------------------------------------------------------
    Matrix( float i_00, float i_10, float i_20, float i_30,
            float i_01, float i_11, float i_21, float i_31,
            float i_02, float i_12, float i_22, float i_32,
            float i_03, float i_13, float i_23, float i_33);
    // --------------------------------------------------------------------------
    /// \brief Destructor
    ~Matrix();
    // --------------------------------------------------------------------------
    /// \brief Set matrix to identity matrix
    void AsIdentity();
    float Determinant() const;
    Matrix Transpose() const;
    Matrix Inverse() const;
    // --------------------------------------------------------------------------
    /// \brief operator * overload, get cross product of two matrix
    /// \other i_other othereter matrix
    /// \return result matrixc
    Matrix operator * ( const Matrix& i_other ) const;
    // --------------------------------------------------------------------------
    /// \brief Operator * overload, get product of a matrix and a vector
    /// \other i_other othereter vector
    /// \return result vector
    Vector operator * ( const Vector& i_other ) const;
    // --------------------------------------------------------------------------
    /// \brief Operator = overload, set othereter matrix value to this matrix
    /// \other i_other
    /// \return 
    Matrix& operator = ( const Matrix& i_other );
    float operator () ( uint32_t i_x, uint32_t i_y ) const;
    float& operator () ( uint32_t i_x, uint32_t i_y );
    void PrintMatrix();
private:
    // --------------------------------------------------------------------------
    /// \4*4 matrix members, array share same space with 16 floats for easy access
    union
    {
        struct
        {
            float  m00,m10,m20,m30,// m00,m01,m02,m0
                   m01,m11,m21,m31,// m10,m11,m12,m13
                   m02,m12,m22,m32,// m20,m21,m22,m23
                   m03,m13,m23,m33;// m30,m31,m32,m33
        };
        float m_mat[16];
    };
};//end of class
}//end of namespace
#endif //end of define
