#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <vector>
#include "color.h"
#include "vector2D.h"
#include <Magick++.h>

namespace rayTracer
{
class Texture
{
public:
	Texture ();
	Texture ( uint32_t _height, uint32_t _width );
    void LoadImage(const std::string& _filename);
	void MakeChecker ();
	const Color& GetColorBilinear ( const Vector2D& _texCoord ) const;
	uint32_t Height() const { return m_height; }
	uint32_t Width() const { return m_width; }
	const Color& operator[] (uint32_t _index ) { assert( _index < m_height* m_width); return m_colors[_index]; }

private:
	uint32_t m_height;
	uint32_t m_width;
	std::vector < Color > m_colors;
};
}//end of namespace
#endif
