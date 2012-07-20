#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>
#include <assert.h>
#include <Magick++.h>
#include "vector2D.h"
#include "color.h"

namespace rayTracer
{
class Image
{
public:
	Image( uint32_t _width, uint32_t _height, const Color& _color);
	Image();
	~Image();

    void ReadFile( const std::string& _fileName );
	void MakeChecker();
    bool WriteTga( const std::string& _fileName );

    const Color& Get( uint32_t _x, uint32_t _y) const;
	Color GetColorBilinear( const Vector2D& _texCoord ) const;
    //set
    void Set( uint32_t _x, uint32_t _y, const Color& _value);

    uint32_t Width() const { return m_width; }
    uint32_t Height() const { return m_height; }
private:
    uint32_t m_width;
    uint32_t m_height;
    std::vector< Color > m_pixels;
};//end of class
}//end of namespace
#endif //end of define
