#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "texture.h"
//#include "vector.h"

namespace rayTracer
{
class Shape;
class Vector;

class Material
{
public:
	Material ();
	Material ( float _reflective, float _refractive, const Shape* _pShape = 0, float _index = 0, float _attenuation = 0.1 );
	Material ( const Material& _material );
	Material& operator = ( const Material& _other );

	Color GetColor( const Vector& _position ) const;

	float Index () const { return m_index; };
	float Reflection () const { return m_reflection; }
	float Refraction () const { return m_refraction; }
	float Attenuation () const { return m_attenuation; }
	const Texture* GetTexture () const { return m_pTexture; }
	void SetTexture ( const Texture* _texture ) { m_pTexture = _texture; }

private:
	///\coefficient for reflection
	float m_reflection;
	///\coefficient for refraction
	float m_refraction;
	const Shape* m_pShape;
	float m_index;
	///\coefficient for attenuation
	float m_attenuation;
	const Texture* m_pTexture;
};
}//end of namespace
#endif
