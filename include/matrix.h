#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string.h>
#include "vector.h"

namespace rayTracer
{
class Matrix
{
public:
    // --------------------------------------------------------------------------
    /// \brief Constructor
    Matrix ();
    // --------------------------------------------------------------------------
    Matrix ( Vector i_row1, Vector i_row2, Vector i_row3, Vector i_row4 );
    // --------------------------------------------------------------------------
    /// \brief Destructor
    ~Matrix ();
    // --------------------------------------------------------------------------
    /// \brief Set matrix to identity matrix
    void AsIdentity ();
    float Determinant () const;
    Matrix Transpose () const;
    Matrix Inverse () const;
    // --------------------------------------------------------------------------
    /// \brief operator * overload, get cross product of two matrix
    /// \other i_other othereter matrix
    /// \return result matrixc
    Matrix operator * ( const Matrix& i_other ) const;
    Matrix operator * ( float i_other ) const;
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
    Vector operator [] ( uint32_t i_index ) const;
    Vector& operator []  ( uint32_t i_index );
    void PrintMatrix();
private:
    // --------------------------------------------------------------------------
    #if 0
    union
    {
        struct
        {
            float  m00,m10,m20,m30,// m00,m01,m02,m0
                   m01,m11,m21,m31,// m10,m11,m12,m13
                   m02,m12,m22,m32,// m20,m21,m22,m23
                   m03,m13,m23,m33;// m30,m31,m32,m33
        };
        Vector m_mat[3];
    };
#endif
    Vector m_mat[3];
};//end of class
//------------------------------------------------------------------------------
inline Vector Matrix::operator [] ( uint32_t i_index ) const
{
    assert ( i_index );
    return m_mat[i_index];
}
//------------------------------------------------------------------------------
inline Vector& Matrix::operator []  ( uint32_t i_index )
{
    assert ( i_index );
    return m_mat[i_index];
}
}//end of namespace
#endif //end of define
