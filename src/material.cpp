#include "material.h"
namespace rayTracer
{
//---------------------------------------------------------------------------------------
Material::Material()
: m_reflection ( 0 ),
  m_refraction ( 0 ),
  m_index ( 0 ),
  m_attenuation ( 0.1 ),
  m_pTexture ( 0 )
{}
//---------------------------------------------------------------------------------------
Material::Material ( float _reflective, float _refractive, float _index, float _attenuation )
: m_reflection ( _reflective ),
  m_refraction ( _refractive ),
  m_index ( _index ),
  m_attenuation ( _attenuation ),
  m_pTexture ( 0 )
{}
//---------------------------------------------------------------------------------------
Material::Material ( const Material& _material )
: m_reflection ( _material.m_reflection ),
  m_refraction ( _material.m_refraction ),
  m_index ( _material.m_index ),
  m_attenuation ( _material.m_attenuation ),
  m_pTexture ( _material.m_pTexture )
{}
//---------------------------------------------------------------------------------------
Material& Material::operator = ( const Material& _other )
{
    m_reflection = _other.m_reflection;
    m_refraction = _other.m_refraction;
    m_index = _other.m_index;
    m_attenuation = _other.m_attenuation;
    m_pTexture = _other.m_pTexture;
    return *this;
}
}
