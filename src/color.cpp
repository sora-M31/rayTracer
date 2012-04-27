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
Color::Color ( const Color& i_other )
:m_r ( i_other.m_r ),
 m_g ( i_other.m_g ),
 m_b ( i_other.m_b ),
 m_a ( i_other.m_a )
{
}
//------------------------------------------------------------------------------
Color::Color ( float i_r,float i_g,float i_b, float i_a )
:m_r ( i_r ),
 m_g ( i_g ),
 m_b ( i_b ),
 m_a ( i_a )
{
}
//------------------------------------------------------------------------------
Color Color::operator + ( const Color& i_other )
{
    return Color ( m_r + i_other.m_r,
                   m_g + i_other.m_g,
                   m_b + i_other.m_b,
                   m_a + i_other.m_a );
}
//------------------------------------------------------------------------------
Color Color::operator * ( float i_other )
{
    return Color ( m_r * i_other,
                   m_g * i_other,
                   m_b * i_other,
                   m_a * i_other );
}
//------------------------------------------------------------------------------
Color Color::operator / ( float i_other )
{
    return Color ( m_r / i_other,
                   m_g / i_other,
                   m_b / i_other,
                   m_a / i_other );
}
//------------------------------------------------------------------------------
Color& Color::operator = ( const Color& i_other )
{
    m_r = i_other.m_r;
    m_g = i_other.m_g;
    m_b = i_other.m_b;
    m_a = i_other.m_a;
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator += ( const Color& i_other )
{
    m_r += i_other.m_r;
    m_g += i_other.m_g;
    m_b += i_other.m_b;
    m_a += i_other.m_a;
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator *= ( float i_other )
{
    m_r *= i_other;
    m_g *= i_other;
    m_b *= i_other;
    m_a *= i_other;
    return *this;
}
//------------------------------------------------------------------------------
Color& Color::operator /= ( float i_other )
{
    m_r /= i_other;
    m_g /= i_other;
    m_b /= i_other;
    m_a /= i_other;
    return *this;
}
inline float Color::r() const
{
    return m_r;
}
//------------------------------------------------------------------------------
inline float Color::g() const
{
    return m_g;
}
//------------------------------------------------------------------------------
inline float Color::b() const
{
    return m_b;
}
//------------------------------------------------------------------------------
inline float Color::a() const
{
    return m_a;
}
//------------------------------------------------------------------------------
void Color::PrintColor()
{
    std::cout<< "Color " << m_r << " " << m_g << " " << m_b << " " << m_a << " \n";
}
}//end of namespace
