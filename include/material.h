#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "Image.h"
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

	Material();
	Material( float _ka, float _kd, float _ks, float _km, float _kf, float _kg,
			  float _index, float _attenuation, const Color& _color = Color(1,1,1,1), bool _aniso = false );
	Material ( const Material& _material );
	Material& operator = ( const Material& _other );

	void SetColor( const Color& _color );
	Color GetColor( const Vector2D& _texCoord ) const;
	Color GetColor() const { return m_color; }

	float ka() const { return m_ka; }
	float kd() const { return m_kd; }
	float ks() const { return m_ks; }
	float km() const { return m_km; }
	float kg() const { return m_kg; }
	float kf() const { return m_kf; }
	bool IsAnisotropic() const { return m_aniso; }
	float Index() const { return m_index; };
	float Attenuation () const { return m_attenuation; }
	const Image* GetTexture () const { return m_pTexture; }
	void SetTexture ( const Image* _texture ) { m_pTexture = _texture; }

private:
	/// \m_ka ambient coefficient
	float m_ka;
	/// \m_kd diffuse coefficient
	float m_kd;
	/// \m_ks specular coefficient
	float m_ks;
	/// \m_km mirror coefficient
	float m_km;
	/// \m_kf fresnel coefficient
	float m_kf;
	/// \m_kg glossy reflection coefficient
	float m_kg;
	/// \refraction index
	float m_index;
	///\coefficient for attenuation
	float m_attenuation;
	///\ Material color when there's no texture
	Color m_color;
	bool m_aniso;
	const Image* m_pTexture;
};
}//end of namespace
#endif
