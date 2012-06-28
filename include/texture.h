#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <vector>
#include "color.h"
#include "vector2D.h"

namespace rayTracer
{
class Texture
{
public:
	Texture ();
	Texture ( uint32_t _height, uint32_t _width );
	void MakeChecker ();
	const Color& GetColorBilinear ( const Vector2D& _texCoord ) const;

private:
	uint32_t m_height;
	uint32_t m_width;
	std::vector < Color > m_colors;
};
}//end of namespace
#endif
