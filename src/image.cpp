#include "image.h"
#include<fstream>
namespace rayTracer
{
//------------------------------------------------------------------------------
Image::Image ()
{}
//------------------------------------------------------------------------------
Image::Image ( uint32_t _width, uint32_t _height)
: m_width ( _width ),
  m_height( _height),
  m_pixels( _width * _height )
{}
//------------------------------------------------------------------------------
Image::~Image ()
{}
//------------------------------------------------------------------------------
bool Image::WriteTga ( const char* _fileName )
{
    std::ofstream tgaImage ( _fileName, std::ios_base::binary );

    if ( !tgaImage.is_open() ) return false;
    //draw header
    unsigned char header[] =
    {
        0,
        0,
        2, // not compressed
        0,0,0,0,
        0,0,0,0,0,

        m_width & 0x00FF,
        ( m_width & 0xFF00) / 256 ,
        m_height & 0x00FF,
        ( m_height & 0xFF00 ) / 256,
        32,//32bit 1 pixel 4 bytes, b,g,r,a
        0
    };
    tgaImage.write ( ( const char* ) header, ( int ) sizeof ( header ) );
    //draw pixel
    uint32_t pixelSize = m_pixels.size();
    for( uint32_t i = 0; i< pixelSize; ++i)
    {
        m_pixels[i].Clamp();
        tgaImage.put ( (unsigned char) ( m_pixels[i].b() * 255.0) );
        tgaImage.put ( (unsigned char) ( m_pixels[i].g() * 255.0) );
        tgaImage.put ( (unsigned char) ( m_pixels[i].r() * 255.0) );
        tgaImage.put ( (unsigned char) ( m_pixels[i].a() * 255.0) );
    }
    tgaImage.close();
    return true;
}
//------------------------------------------------------------------------------
const Color& Image::Get ( uint32_t _x, uint32_t _y) const
{
    return m_pixels [ m_width * _y + _x ];
}
//------------------------------------------------------------------------------
void Image::Set ( uint32_t _x, uint32_t _y, const Color& _value)
{
    m_pixels [ m_width * _y + _x ] = _value;
}
}//end of namespace
