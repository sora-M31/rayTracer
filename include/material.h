#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "texture.h"
//#include "vector2D.h"

namespace rayTracer
{
class Shape;
class Vector;
class Vector2D;

class Material
{
public:
	//static const Material kAir;

	Material ();
	Material ( float _kd, float _ks, float _km, float _kg, float _kr, float _index, float _attenuation, const Color& _color = Color(1,1,1,1) );
	Material ( const Material& _material );
	Material& operator = ( const Material& _other );

	//Color GetColor( const Vector& _position ) const;
	void SetColor ( const Color& _color );
	Color GetColor( const Vector2D& _texCoord ) const;
	Color GetColor() const { return m_color; }

	float Index () const { return m_index; };
	float kDiffuse () const { return m_kd; }
	float kSpecular () const { return m_ks; }
	float kMirror () const { return m_km; }
	float kGlossy () const { return m_kg; }
	float kRefraction () const { return m_kr; }
	float Attenuation () const { return m_attenuation; }
	const Texture* GetTexture () const { return m_pTexture; }
	void SetTexture ( const Texture* _texture ) { m_pTexture = _texture; }

private:
	float m_kd;
	float m_ks;
	float m_km;
	float m_kg;
	float m_kr;
	//refraction index
	float m_index;
	///\coefficient for attenuation
	float m_attenuation;
	Color m_color;
	const Texture* m_pTexture;
};
}//end of namespace
#endif
