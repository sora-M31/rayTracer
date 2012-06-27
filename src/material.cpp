#include "material.h"
#include "shape.h"
namespace rayTracer
{
//Material::kAir(foobar);

//---------------------------------------------------------------------------------------
Material::Material()
: m_reflection ( 0 ),
  m_refraction ( 0 ),
  m_pShape ( 0 ),
  m_index ( 0 ),
  m_attenuation ( 0.1 ),
  m_pTexture ( 0 )
{}
//---------------------------------------------------------------------------------------
Material::Material ( float _reflective, float _refractive, const Shape* _pShape, float _index, float _attenuation )
: m_reflection ( _reflective ),
  m_refraction ( _refractive ),
  m_pShape ( _pShape ),
  m_index ( _index ),
  m_attenuation ( _attenuation ),
  m_pTexture ( 0 )
{}
//---------------------------------------------------------------------------------------
Material::Material ( const Material& _material )
: m_reflection ( _material.m_reflection ),
  m_refraction ( _material.m_refraction ),
  m_pShape ( _material.m_pShape ),
  m_index ( _material.m_index ),
  m_attenuation ( _material.m_attenuation ),
  m_pTexture ( _material.m_pTexture )
{}
//---------------------------------------------------------------------------------------
Material& Material::operator = ( const Material& _other )
{
    m_reflection = _other.m_reflection;
    m_refraction = _other.m_refraction;
    m_pShape = _other.m_pShape;
    m_index = _other.m_index;
    m_attenuation = _other.m_attenuation;
    m_pTexture = _other.m_pTexture;
    return *this;
}
//---------------------------------------------------------------------------------------
Color Material::GetColor( const Vector2D& _texCoord ) const
{
    Color color ( 1,1,1,1 );
    if ( m_pTexture != 0 )
        color = m_pTexture->GetColorBilinear( _texCoord.u(), _texCoord.v() );
    return color;
}
#if 0
Color Material::GetColor( const Vector& _position ) const
{
    float u(0);
    float v(0);
    assert ( m_pShape != 0 );
    m_pShape->ToUVSpace ( _position, u, v );
    Color color ( 1,1,1,1 );
    if ( m_pTexture != 0 )
        color = m_pTexture->GetColorBilinear( u, v );
    return color;
}
#endif
}//end of namespace
