#include "color.h"
#include <string.h>
#include <iostream>
namespace rayTracer
{
//------------------------------------------------------------------------------
Color::Color ()
{
    memset( m_data, '0', 4 );
}
//------------------------------------------------------------------------------
Color::~Color ()
{}
//------------------------------------------------------------------------------
Color::Color ( const Color& _other )
{
    m_data[0] = _other.m_data[0];
    m_data[1] = _other.m_data[1];
    m_data[2] = _other.m_data[2];
    m_data[3] = _other.m_data[3];
}
//------------------------------------------------------------------------------
Color::Color ( float _r,float _g,float _b, float _a )
{
    m_data[0] = _r;
    m_data[1] = _g;
    m_data[2] = _b;
    m_data[3] = _a;
}
//------------------------------------------------------------------------------
Color Color::operator + ( const Color& _other ) const
{
    return Color ( m_data[0] + _other.m_data[0],
                   m_data[1] + _other.m_data[1],
                   m_data[2] + _other.m_data[2],
                   m_data[3] + _other.m_data[3] );
}
//------------------------------------------------------------------------------
Color Color::operator * ( float _other ) const
{
    return Color ( m_data[0] * _other,
                   m_data[1] * _other,
                   m_data[2] * _other,
                   1.0f );
}
//------------------------------------------------------------------------------
Color Color::operator / ( float _other ) const 
{
    return Color ( m_data[0] / _other,
                   m_data[1] / _other,
                   m_data[2] / _other,
                   m_data[3] / _other );
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
    m_data[3] += _other.m_data[3];
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator *= ( float _other )
{
    m_data[0] *= _other;
    m_data[1] *= _other;
    m_data[2] *= _other;
    m_data[3] *= _other;
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator /= ( float _other )
{
    m_data[0] /= _other;
    m_data[1] /= _other;
    m_data[2] /= _other;
    m_data[3] /= _other;
    return *this;
}
//------------------------------------------------------------------------------
void Color::PrintColor()
{
    std::cout<< "Color " << m_data[0] << " " << m_data[1] << " " << m_data[2] << " " << m_data[3] << " \n";
}
}//end of namespace
