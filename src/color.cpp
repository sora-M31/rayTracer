#include "color.h"
#include <string.h>
#include <iostream>
#include <math.h>
namespace rayTracer
{
//------------------------------------------------------------------------------
Color::Color()
{
    memset( m_data, '0', 4 );
}
//------------------------------------------------------------------------------
Color::~Color()
{}
//------------------------------------------------------------------------------
Color::Color( const Color& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    m_data[2] = _other.m_data[2];
    m_data[3] = _other.m_data[3];
}
//------------------------------------------------------------------------------
Color::Color( float _r,float _g,float _b, float _a )
{
    m_data[0] = _r;
    m_data[1] = _g;
    m_data[2] = _b;
    m_data[3] = _a;
}
//------------------------------------------------------------------------------
Color Color::operator + ( const Color& _other ) const
{
    return Color( m_data[0] + _other.m_data[0],
                  m_data[1] + _other.m_data[1],
                  m_data[2] + _other.m_data[2],
                  m_data[3] );
}
//------------------------------------------------------------------------------
Color Color::operator * ( float _other ) const
{
    return Color( m_data[0] * _other,
                  m_data[1] * _other,
                  m_data[2] * _other,
                  m_data[3]  );
                   //1.0f );
}
//------------------------------------------------------------------------------
Color Color::operator * ( const Color& _other ) const
{
    return  Color( m_data[0] * _other.m_data[0],
                   m_data[1] * _other.m_data[1],
                   m_data[2] * _other.m_data[2],
                   1.0 );
}
//------------------------------------------------------------------------------
Color Color::operator / ( float _other ) const
{
    return Color( m_data[0] / _other,
                  m_data[1] / _other,
                  m_data[2] / _other,
                  m_data[3]  );
                   //1.0f );
}
//------------------------------------------------------------------------------
Color& Color::operator = ( const Color& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    m_data[2] = _other.m_data[2];
    m_data[3] = _other.m_data[3];
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator += ( const Color& _other )
{
    m_data[0] += _other.m_data[0];
    m_data[1] += _other.m_data[1];
    m_data[2] += _other.m_data[2];
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator *= ( float _other )
{
    m_data[0] *= _other;
    m_data[1] *= _other;
    m_data[2] *= _other;
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator /= ( float _other )
{
    m_data[0] /= _other;
    m_data[1] /= _other;
    m_data[2] /= _other;
    return *this;
}
//------------------------------------------------------------------------------
void Color::PrintColor() const
{
    std::cout<< "Color " << m_data[0] << " " << m_data[1] << " " << m_data[2] << " " << m_data[3] << " \n";
}
//------------------------------------------------------------------------------
void Color::Clamp()
{
    for( uint32_t i = 0; i< 4; ++i )
    {
        if( m_data[i] > 1 )
            m_data[i] = 1;
        else if ( m_data[i] < 0 )
            m_data[i] = 0;
    }
}
//------------------------------------------------------------------------------
void Color::SetExposure( float _t )
{
    m_data[0] = 1.0 - exp( m_data[0] * _t );
    m_data[1] = 1.0 - exp( m_data[1] * _t );
    m_data[2] = 1.0 - exp( m_data[2] * _t );
}
}//end of namespace
