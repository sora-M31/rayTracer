#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>
#include <assert.h>
#include <Magick++.h>
#include "vector2D.h"
#include "color.h"

namespace rayTracer
{
// --------------------------------------------------------------------------
/// \brief Image class, for loading texture and write final images
class Image
{
public:
	Image( uint32_t _width, uint32_t _height, const Color& _color);
	Image( const std::string& _fileName );
	~Image();

	// --------------------------------------------------------------------------
	/// \brief Load image for texture using magick++
	/// \param _fileName
    void ReadFile( const std::string& _fileName );
	// --------------------------------------------------------------------------
	/// \brief Make checker pattern
	void MakeChecker();
    bool WriteTga( const std::string& _fileName );

    const Color& Get( uint32_t _x, uint32_t _y) const;
	// --------------------------------------------------------------------------
	/// \brief Get color with with texture coordinate provided using bilinear filtering
	/// \param _texCoord
	/// \return Color
	Color GetColorBilinear( const Vector2D& _texCoord ) const;
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
