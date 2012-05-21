#include "matrix.h"
#include <stdint.h>
#include <assert.h>

namespace rayTracer
{
//------------------------------------------------------------------------------
Matrix::Matrix ()
{
    AsIdentity();
}
//------------------------------------------------------------------------------
Matrix::Matrix ( Vector i_row1, Vector i_row2, Vector i_row3, Vector i_row4 )
{
  m_mat[0] = i_row1;
  m_mat[1] = i_row2;
  m_mat[2] = i_row3;
  m_mat[3] = i_row4;
}
//------------------------------------------------------------------------------
Matrix::Matrix ( float _00, float _01, float _02, float _03,
         float _10, float _11, float _12, float _13,
         float _20, float _21, float _22, float _23,
         float _30, float _31, float _32, float _33 )
{
    m_mat[0] = Vector ( _00, _01, _02, _03 );
    m_mat[1] = Vector ( _10, _11, _12, _13 );
    m_mat[2] = Vector ( _20, _21, _22, _23 );
    m_mat[3] = Vector ( _30, _31, _32, _33 );
}
//------------------------------------------------------------------------------
Matrix::~Matrix ()
{
}
//------------------------------------------------------------------------------
void Matrix::AsIdentity ()
{
    m_mat[0] = Vector ( 1, 0, 0, 0 );
    m_mat[1] = Vector ( 0, 1, 0, 0 );
    m_mat[2] = Vector ( 0, 0, 1, 0 );
    m_mat[3] = Vector ( 0, 0, 0, 1 );
}
//------------------------------------------------------------------------------
float Matrix::Determinant () const
{
    float det = ( m_mat[0][0] * m_mat[1][1] * m_mat[2][2] * m_mat[3][3] + m_mat[0][0] * m_mat[1][2] * m_mat[2][3] * m_mat[3][1] + m_mat[0][0] * m_mat[1][3] * m_mat[2][1] * m_mat[3][2] );
         det += ( m_mat[0][1] * m_mat[1][0] * m_mat[2][3] * m_mat[3][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0] * m_mat[3][3] + m_mat[0][1] * m_mat[1][3] * m_mat[2][2] * m_mat[3][0] );
         det += ( m_mat[0][2] * m_mat[1][0] * m_mat[2][1] * m_mat[3][3] + m_mat[0][2] * m_mat[1][1] * m_mat[2][3] * m_mat[3][0] + m_mat[0][2] * m_mat[1][3] * m_mat[2][0] * m_mat[3][1] );
         det += ( m_mat[0][3] * m_mat[1][0] * m_mat[2][2] * m_mat[3][1] + m_mat[0][3] * m_mat[1][1] * m_mat[2][0] * m_mat[3][2] + m_mat[0][3] * m_mat[1][2] * m_mat[2][1] * m_mat[3][0] );
         det -= ( m_mat[0][0] * m_mat[1][1] * m_mat[2][3] * m_mat[3][2] + m_mat[0][0] * m_mat[1][2] * m_mat[2][1] * m_mat[3][3] + m_mat[0][0] * m_mat[1][3] * m_mat[2][2] * m_mat[3][1] );
         det -= ( m_mat[0][1] * m_mat[1][0] * m_mat[2][2] * m_mat[3][3] + m_mat[0][1] * m_mat[1][2] * m_mat[2][3] * m_mat[3][0] + m_mat[0][1] * m_mat[1][3] * m_mat[2][0] * m_mat[3][2] );
         det -= ( m_mat[0][2] * m_mat[1][0] * m_mat[2][3] * m_mat[3][1] + m_mat[0][2] * m_mat[1][1] * m_mat[2][0] * m_mat[3][3] + m_mat[0][2] * m_mat[1][3] * m_mat[2][1] * m_mat[3][0] );
         det -= ( m_mat[0][3] * m_mat[1][0] * m_mat[2][1] * m_mat[3][2] + m_mat[0][3] * m_mat[1][1] * m_mat[2][2] * m_mat[3][0] + m_mat[0][3] * m_mat[1][2] * m_mat[2][0] * m_mat[3][1] );
    return det;
}
//------------------------------------------------------------------------------
Matrix Matrix::Transpose () const
{
    return Matrix ( Vector ( m_mat[0][0], m_mat[1][0], m_mat[2][0], m_mat[3][0] ),
                    Vector ( m_mat[0][1], m_mat[1][1], m_mat[2][1], m_mat[3][1] ),
                    Vector ( m_mat[0][2], m_mat[1][2], m_mat[2][2], m_mat[3][2] ),
                    Vector ( m_mat[0][3], m_mat[1][3], m_mat[2][3], m_mat[3][3] ) );
}
//------------------------------------------------------------------------------
Matrix Matrix::Inverse () const
{
    Vector tmp0, tmp1, tmp2, tmp3;

    tmp0[0] = m_mat[1][1]*m_mat[2][2]*m_mat[3][3] + m_mat[1][2]*m_mat[2][3]*m_mat[3][1] + m_mat[1][3]*m_mat[2][1]*m_mat[3][2] - m_mat[1][1]*m_mat[2][3]*m_mat[3][2] - m_mat[1][2]*m_mat[2][1]*m_mat[3][3] - m_mat[1][3]*m_mat[2][2]*m_mat[3][1];
    tmp0[1] = m_mat[0][1]*m_mat[2][3]*m_mat[3][2] + m_mat[0][2]*m_mat[2][1]*m_mat[3][3] + m_mat[0][3]*m_mat[2][2]*m_mat[3][1] - m_mat[0][1]*m_mat[2][2]*m_mat[3][3] - m_mat[0][2]*m_mat[2][3]*m_mat[3][1] - m_mat[0][3]*m_mat[2][1]*m_mat[3][2];
    tmp0[2] = m_mat[0][1]*m_mat[1][2]*m_mat[3][3] + m_mat[0][2]*m_mat[1][3]*m_mat[3][1] + m_mat[0][3]*m_mat[1][1]*m_mat[3][2] - m_mat[0][1]*m_mat[1][3]*m_mat[3][2] - m_mat[0][2]*m_mat[1][1]*m_mat[3][3] - m_mat[0][3]*m_mat[1][2]*m_mat[3][1];
    tmp0[3] = m_mat[0][1]*m_mat[1][3]*m_mat[2][2] + m_mat[0][2]*m_mat[1][1]*m_mat[2][3] + m_mat[0][3]*m_mat[1][2]*m_mat[2][1] - m_mat[0][1]*m_mat[1][2]*m_mat[2][3] - m_mat[0][2]*m_mat[1][3]*m_mat[2][1] - m_mat[0][3]*m_mat[1][1]*m_mat[2][2];
    tmp1[0] = m_mat[1][0]*m_mat[2][3]*m_mat[3][2] + m_mat[1][2]*m_mat[2][0]*m_mat[3][3] + m_mat[1][3]*m_mat[2][2]*m_mat[3][0] - m_mat[1][0]*m_mat[2][2]*m_mat[3][3] - m_mat[1][2]*m_mat[2][3]*m_mat[3][0] - m_mat[1][3]*m_mat[2][0]*m_mat[3][2];
    tmp1[1] = m_mat[0][0]*m_mat[2][2]*m_mat[3][3] + m_mat[0][2]*m_mat[2][3]*m_mat[3][0] + m_mat[0][3]*m_mat[2][0]*m_mat[3][2] - m_mat[0][0]*m_mat[2][3]*m_mat[3][2] - m_mat[0][2]*m_mat[2][0]*m_mat[3][3] - m_mat[0][3]*m_mat[2][2]*m_mat[3][0];
    tmp1[2] = m_mat[0][0]*m_mat[1][3]*m_mat[3][2] + m_mat[0][2]*m_mat[1][0]*m_mat[3][3] + m_mat[0][3]*m_mat[1][2]*m_mat[3][0] - m_mat[0][0]*m_mat[1][2]*m_mat[3][3] - m_mat[0][2]*m_mat[1][3]*m_mat[3][0] - m_mat[0][3]*m_mat[1][0]*m_mat[3][2];
    tmp1[3] = m_mat[0][0]*m_mat[1][2]*m_mat[2][3] + m_mat[0][2]*m_mat[1][3]*m_mat[2][0] + m_mat[0][3]*m_mat[1][0]*m_mat[2][2] - m_mat[0][0]*m_mat[1][3]*m_mat[2][2] - m_mat[0][2]*m_mat[1][0]*m_mat[2][3] - m_mat[0][3]*m_mat[1][2]*m_mat[2][0];
    tmp2[0] = m_mat[1][0]*m_mat[2][1]*m_mat[3][3] + m_mat[1][1]*m_mat[2][3]*m_mat[3][0] + m_mat[1][3]*m_mat[2][0]*m_mat[3][1] - m_mat[1][0]*m_mat[2][3]*m_mat[3][1] - m_mat[1][1]*m_mat[2][0]*m_mat[3][3] - m_mat[1][3]*m_mat[2][1]*m_mat[3][0];
    tmp2[1] = m_mat[0][0]*m_mat[2][3]*m_mat[3][1] + m_mat[0][1]*m_mat[2][0]*m_mat[3][3] + m_mat[0][3]*m_mat[2][1]*m_mat[3][0] - m_mat[0][0]*m_mat[2][1]*m_mat[3][3] - m_mat[0][1]*m_mat[2][3]*m_mat[3][0] - m_mat[0][3]*m_mat[2][0]*m_mat[3][1];
    tmp2[2] = m_mat[0][0]*m_mat[1][1]*m_mat[3][3] + m_mat[0][1]*m_mat[1][3]*m_mat[3][0] + m_mat[0][3]*m_mat[1][0]*m_mat[3][1] - m_mat[0][0]*m_mat[1][3]*m_mat[3][1] - m_mat[0][1]*m_mat[1][0]*m_mat[3][3] - m_mat[0][3]*m_mat[1][1]*m_mat[3][0];
    tmp2[3] = m_mat[0][0]*m_mat[1][3]*m_mat[2][1] + m_mat[0][1]*m_mat[1][0]*m_mat[2][3] + m_mat[0][3]*m_mat[1][1]*m_mat[2][0] - m_mat[0][0]*m_mat[1][1]*m_mat[2][3] - m_mat[0][1]*m_mat[1][3]*m_mat[2][0] - m_mat[0][3]*m_mat[1][0]*m_mat[2][1];
    tmp3[0] = m_mat[1][0]*m_mat[2][2]*m_mat[3][1] + m_mat[1][1]*m_mat[2][0]*m_mat[3][2] + m_mat[1][2]*m_mat[2][1]*m_mat[3][0] - m_mat[1][0]*m_mat[2][1]*m_mat[3][2] - m_mat[1][1]*m_mat[2][2]*m_mat[3][0] - m_mat[1][2]*m_mat[2][0]*m_mat[3][1];
    tmp3[1] = m_mat[0][0]*m_mat[2][1]*m_mat[3][2] + m_mat[0][1]*m_mat[2][2]*m_mat[3][0] + m_mat[0][2]*m_mat[2][0]*m_mat[3][1] - m_mat[0][0]*m_mat[2][2]*m_mat[3][1] - m_mat[0][1]*m_mat[2][0]*m_mat[3][2] - m_mat[0][2]*m_mat[2][1]*m_mat[3][0];
    tmp3[2] = m_mat[0][0]*m_mat[1][2]*m_mat[3][1] + m_mat[0][1]*m_mat[1][0]*m_mat[3][2] + m_mat[0][2]*m_mat[1][1]*m_mat[3][0] - m_mat[0][0]*m_mat[1][1]*m_mat[3][2] - m_mat[0][1]*m_mat[1][2]*m_mat[3][0] - m_mat[0][2]*m_mat[1][0]*m_mat[3][1];
    tmp3[3] = m_mat[0][0]*m_mat[1][1]*m_mat[2][2] + m_mat[0][1]*m_mat[1][2]*m_mat[2][0] + m_mat[0][2]*m_mat[1][0]*m_mat[2][1] - m_mat[0][0]*m_mat[1][2]*m_mat[2][1] - m_mat[0][1]*m_mat[1][0]*m_mat[2][2] - m_mat[0][2]*m_mat[1][1]*m_mat[2][0];

    assert ( Determinant()!=0 );
    float invDet = 1.0 / Determinant ();

    return Matrix ( tmp0, tmp1, tmp2, tmp3 ) * invDet;
}
//------------------------------------------------------------------------------
Matrix& Matrix::operator = ( const Matrix& i_other )
{
    for ( uint32_t i=0; i<4; ++i )
    {
        m_mat[i] = i_other.m_mat[i];
    }
    return *this;
}
//------------------------------------------------------------------------------
Vector Matrix::operator * ( const Vector& i_other ) const
{
    return Vector ( m_mat[0].Dot4 ( i_other ),
                    m_mat[1].Dot4 ( i_other ),
                    m_mat[2].Dot4 ( i_other ),
                    m_mat[3].Dot4 ( i_other ) );
}
//------------------------------------------------------------------------------
Matrix Matrix::operator * ( const Matrix& i_other ) const
{
    Matrix tmp = i_other.Transpose();

    return Matrix ( Vector ( m_mat[0].Dot4(tmp[0]), m_mat[0].Dot4(tmp[1]), m_mat[0].Dot4(tmp[2]), m_mat[0].Dot4(tmp[3]) ),
                    Vector ( m_mat[1].Dot4(tmp[0]), m_mat[1].Dot4(tmp[1]), m_mat[1].Dot4(tmp[2]), m_mat[1].Dot4(tmp[3]) ),
                    Vector ( m_mat[2].Dot4(tmp[0]), m_mat[2].Dot4(tmp[1]), m_mat[2].Dot4(tmp[2]), m_mat[2].Dot4(tmp[3]) ),
                    Vector ( m_mat[3].Dot4(tmp[0]), m_mat[3].Dot4(tmp[1]), m_mat[3].Dot4(tmp[2]), m_mat[3].Dot4(tmp[3]) )
    );
}
//------------------------------------------------------------------------------
Matrix Matrix::operator * ( float i_other ) const
{
    return Matrix( m_mat[0] * i_other, m_mat[1] * i_other, m_mat [2] * i_other, m_mat[3] * i_other );
}
//------------------------------------------------------------------------------
void Matrix::PrintMatrix ()
{
    std::cout<<m_mat[0]<<"\n"<<m_mat[1]<<"\n"<<m_mat[2]<<"\n"<<m_mat[3]<<"\n";
}
//------------------------------------------------------------------------------
Vector operator * ( const Vector& _left, const Matrix& _right )
{
    return _right * _left;
}

}//end of namespace
