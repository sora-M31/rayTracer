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
    Matrix ( Vector _row1, Vector _row2, Vector _row3, Vector _row4 );
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
    /// \other _other othereter matrix
    /// \return result matrixc
    Matrix operator * ( const Matrix& _other ) const;
    Matrix operator * ( float _other ) const;
    // --------------------------------------------------------------------------
    /// \brief Operator * overload, get product of a matrix and a vector
    /// \other _other othereter vector
    /// \return result vector
    Vector operator * ( const Vector& _other ) const;
    // --------------------------------------------------------------------------
    /// \brief Operator = overload, set othereter matrix value to this matrix
    /// \other _other
    /// \return 
    Matrix& operator = ( const Matrix& _other );
    Vector operator [] ( uint32_t _index ) const;
    Vector& operator []  ( uint32_t _index );
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
inline Vector Matrix::operator [] ( uint32_t _index ) const
{
    assert ( _index );
    return m_mat[_index];
}
//------------------------------------------------------------------------------
inline Vector& Matrix::operator []  ( uint32_t _index )
{
    assert ( _index );
    return m_mat[_index];
}
}//end of namespace
#endif //end of define
