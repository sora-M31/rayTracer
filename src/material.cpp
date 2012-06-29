#include "material.h"
#include "shape.h"
namespace rayTracer
{
//Material::kAir(foobar);

//---------------------------------------------------------------------------------------
Material::Material()
: m_kd ( 0 ),
  m_ks ( 0 ),
  m_km ( 0 ),
  m_index ( 0 ),
  m_attenuation ( 0.1 ),
  m_pTexture ( 0 )
{}
//---------------------------------------------------------------------------------------
Material::Material ( float _kd, float _ks, float _km, float _index, float _attenuation )
: m_kd ( _kd ),
  m_ks ( _ks ),
  m_km ( _km ),
  m_index ( _index ),
  m_attenuation ( _attenuation ),
  m_pTexture ( 0 )
{}
//---------------------------------------------------------------------------------------
Material::Material ( const Material& _material )
: m_kd ( _material.m_kd ),
  m_ks ( _material.m_ks ),
  m_km ( _material.m_km ),
  m_index ( _material.m_index ),
  m_attenuation ( _material.m_attenuation ),
  m_pTexture ( _material.m_pTexture )
{}
//---------------------------------------------------------------------------------------
Material& Material::operator = ( const Material& _other )
{
    m_kd = _other.m_kd;
    m_ks = _other.m_ks;
    m_km = _other.m_km;
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
        color = m_pTexture->GetColorBilinear( _texCoord );
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
