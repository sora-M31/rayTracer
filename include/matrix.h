#ifndef _MATRIX_H_
#define _MATRIX_H_
#include <string.h>
#include "vector.h"

namespace rayTracer
{
class Matrix
{
public:
    Matrix ();
    Matrix ( float _00, float _01, float _02, float _03,
             float _10, float _11, float _12, float _13,
             float _20, float _21, float _22, float _23,
             float _30, float _31, float _32, float _33 );
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
    Vector m_mat[4];
};//end of class
//------------------------------------------------------------------------------
inline Vector Matrix::operator [] ( uint32_t _index ) const
{
    assert ( _index < 4 );
    return m_mat[_index];
}
//------------------------------------------------------------------------------
inline Vector& Matrix::operator []  ( uint32_t _index )
{
    assert ( _index < 4 );
    return m_mat[_index];
}
}//end of namespace
#endif //end of define
