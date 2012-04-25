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
Matrix::Matrix ( float i_00,float i_10,float i_20,float i_30,
                 float i_01,float i_11,float i_21,float i_31,
                 float i_02,float i_12,float i_22,float i_32,
                 float i_03,float i_13,float i_23,float i_33 )
: m00 ( i_00 ), m10 ( i_10 ), m20 ( i_20 ), m30 ( i_30 ),
  m01 ( i_01 ), m11 ( i_11 ), m21 ( i_21 ), m31 ( i_31 ),
  m02 ( i_02 ), m12 ( i_12 ), m22 ( i_22 ), m32 ( i_32 ),
  m03 ( i_03 ), m13 ( i_13 ), m23 ( i_23 ), m33 ( i_33 )
{
}
//------------------------------------------------------------------------------
Matrix::~Matrix ()
{
}
//------------------------------------------------------------------------------
void Matrix::AsIdentity ()
{
    memset ( m_mat, 0.0f, 16.0*sizeof ( float ) );
    m00 = m11 = m22 = m33 = 1.0f;
}
//------------------------------------------------------------------------------
float Matrix::Determinant () const
{
    float det = ( m00*m11*m22*m33 + m00*m12*m23*m31 + m00*m13*m21*m32 );
         det += ( m01*m10*m23*m32 + m01*m12*m20*m33 + m01*m13*m22*m30 );
         det += ( m02*m10*m21*m33 + m02*m11*m23*m30 + m02*m13*m20*m31 );
         det += ( m03*m10*m22*m31 + m03*m11*m20*m32 + m03*m12*m21*m30 );
         det -= ( m00*m11*m23*m32 + m00*m12*m21*m33 + m00*m13*m22*m31 );
         det -= ( m01*m10*m22*m33 + m01*m12*m23*m30 + m01*m13*m20*m32 );
         det -= ( m02*m10*m23*m31 + m02*m11*m20*m33 + m02*m13*m21*m30 );
         det -= ( m03*m10*m21*m32 + m03*m11*m22*m30 + m03*m12*m20*m31 );
    return det;
}
//------------------------------------------------------------------------------
Matrix Matrix::Transpose () const
{
    return Matrix ( m00, m01, m02, m03,
                    m10, m11, m12, m13,
                    m20, m21, m22, m23,
                    m30, m31, m32, m33 );
}
//------------------------------------------------------------------------------
Matrix Matrix::Inverse () const
{
    float tmp00 = m11*m22*m33 + m12*m23*m31 + m13*m21*m32 - m11*m23*m32 - m12*m21*m33 - m13*m22*m31;
    float tmp01 = m01*m23*m32 + m02*m21*m33 + m03*m22*m31 - m01*m22*m33 - m02*m23*m31 - m03*m21*m32;
    float tmp02 = m01*m12*m33 + m02*m13*m31 + m03*m11*m32 - m01*m13*m32 - m02*m11*m33 - m03*m12*m31;
    float tmp03 = m01*m13*m22 + m02*m11*m23 + m03*m12*m21 - m01*m12*m23 - m02*m13*m21 - m03*m11*m22;
    float tmp10 = m10*m23*m32 + m12*m20*m33 + m13*m22*m30 - m10*m22*m33 - m12*m23*m30 - m13*m20*m32;
    float tmp11 = m00*m22*m33 + m02*m23*m30 + m03*m20*m32 - m00*m23*m32 - m02*m20*m33 - m03*m22*m30;
    float tmp12 = m00*m13*m32 + m02*m10*m33 + m03*m12*m30 - m00*m12*m33 - m02*m13*m30 - m03*m10*m32;
    float tmp13 = m00*m12*m23 + m02*m13*m20 + m03*m10*m22 - m00*m13*m22 - m02*m10*m23 - m03*m12*m20;
    float tmp20 = m10*m21*m33 + m11*m23*m30 + m13*m20*m31 - m10*m23*m31 - m11*m20*m33 - m13*m21*m30;
    float tmp21 = m00*m23*m31 + m01*m20*m33 + m03*m21*m30 - m00*m21*m33 - m01*m23*m30 - m03*m20*m31;
    float tmp22 = m00*m11*m33 + m01*m13*m30 + m03*m10*m31 - m00*m13*m31 - m01*m10*m33 - m03*m11*m30;
    float tmp23 = m00*m13*m21 + m01*m10*m23 + m03*m11*m20 - m00*m11*m23 - m01*m13*m20 - m03*m10*m21;
    float tmp30 = m10*m22*m31 + m11*m20*m32 + m12*m21*m30 - m10*m21*m32 - m11*m22*m30 - m12*m20*m31;
    float tmp31 = m00*m21*m32 + m01*m22*m30 + m02*m20*m31 - m00*m22*m31 - m01*m20*m32 - m02*m21*m30;
    float tmp32 = m00*m12*m31 + m01*m10*m32 + m02*m11*m30 - m00*m11*m32 - m01*m12*m30 - m02*m10*m31;
    float tmp33 = m00*m11*m22 + m01*m12*m20 + m02*m10*m21 - m00*m12*m21 - m01*m10*m22 - m02*m11*m20;

    float invDet = 1.0 / Determinant ();

    return Matrix ( tmp00*invDet, tmp10*invDet, tmp20*invDet, tmp30*invDet,
                    tmp01*invDet, tmp11*invDet, tmp21*invDet, tmp31*invDet,
                    tmp02*invDet, tmp12*invDet, tmp22*invDet, tmp32*invDet,
                    tmp03*invDet, tmp13*invDet, tmp23*invDet, tmp33*invDet );
}
//------------------------------------------------------------------------------
Matrix& Matrix::operator = ( const Matrix& i_other )
{
    for ( uint32_t i=0; i<16; ++i )
    {
        m_mat[i] = i_other.m_mat[i];
    }
    return *this;
}
//------------------------------------------------------------------------------
inline Vector Matrix::operator * ( const Vector& i_other ) const
{
    return Vector ( m00*i_other.GetX () + m01*i_other.GetY () + m02*i_other.GetZ () + m03*i_other.GetW (),
                    m10*i_other.GetX () + m11*i_other.GetY () + m12*i_other.GetZ () + m13*i_other.GetW (),
                    m20*i_other.GetX () + m21*i_other.GetY () + m22*i_other.GetZ () + m23*i_other.GetW (),
                    i_other.GetW() );
}
//------------------------------------------------------------------------------
Matrix Matrix::operator * ( const Matrix& i_other ) const
{
    Matrix mat;
    mat.m00 = m00*i_other.m00 + m01 *i_other.m10 + m02 *i_other.m20 + m03*i_other.m30;
    mat.m10 = m10*i_other.m00 + m11 *i_other.m10 + m12 *i_other.m20 + m13*i_other.m30;
    mat.m20 = m20*i_other.m00 + m21 *i_other.m10 + m22 *i_other.m20 + m23*i_other.m30;
    mat.m30 = m30*i_other.m00 + m31 *i_other.m10 + m32 *i_other.m20 + m33*i_other.m30;
    mat.m01 = m00*i_other.m01 + m01 *i_other.m11 + m02 *i_other.m21 + m03*i_other.m31;
    mat.m11 = m10*i_other.m01 + m11 *i_other.m11 + m12 *i_other.m21 + m13*i_other.m31;
    mat.m21 = m20*i_other.m01 + m21 *i_other.m11 + m22 *i_other.m21 + m23*i_other.m31;
    mat.m31 = m30*i_other.m01 + m31 *i_other.m11 + m32 *i_other.m21 + m33*i_other.m31;
    mat.m02 = m00*i_other.m02 + m01 *i_other.m12 + m02 *i_other.m22 + m03*i_other.m32;
    mat.m12 = m10*i_other.m02 + m11 *i_other.m12 + m12 *i_other.m22 + m13*i_other.m32;
    mat.m22 = m20*i_other.m02 + m21 *i_other.m12 + m22 *i_other.m22 + m23*i_other.m32;
    mat.m32 = m30*i_other.m02 + m31 *i_other.m12 + m32 *i_other.m22 + m33*i_other.m32;
    mat.m03 = m00*i_other.m03 + m01 *i_other.m13 + m02 *i_other.m23 + m03*i_other.m33;
    mat.m13 = m10*i_other.m03 + m11 *i_other.m13 + m12 *i_other.m23 + m13*i_other.m33;
    mat.m23 = m20*i_other.m03 + m21 *i_other.m13 + m22 *i_other.m23 + m23*i_other.m33;
    mat.m33 = m30*i_other.m03 + m31 *i_other.m13 + m32 *i_other.m23 + m33*i_other.m33;
    return mat;
}
//------------------------------------------------------------------------------
inline float Matrix::operator [] ( uint32_t i_id ) const
{
    assert ( i_id < 16 );
    return m_mat[ i_id ];
}
//------------------------------------------------------------------------------
inline void Matrix::Set ( uint32_t i_id, float i_value )
{
    assert ( i_id < 16 );
    m_mat[ i_id ] = i_value;
}
//------------------------------------------------------------------------------
void Matrix::PrintMatrix ()
{
    std::cout<<m00<<" "<<m01<<" "<<m02<<" "<<m03<<"\n"
             <<m10<<" "<<m11<<" "<<m12<<" "<<m13<<"\n"
             <<m20<<" "<<m21<<" "<<m22<<" "<<m23<<"\n"
             <<m30<<" "<<m31<<" "<<m32<<" "<<m33<<"\n";
}
}//end of namespace
