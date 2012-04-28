#include "image.h"
#include<fstream>
namespace rayTracer
{
//------------------------------------------------------------------------------
Image::Image ()
{}
//------------------------------------------------------------------------------
Image::Image ( uint32_t i_width, uint32_t i_height)
: m_width ( i_width ),
  m_height( i_height),
  m_pixels( i_width * i_height )
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
        tgaImage.put ( (unsigned char) ( m_pixels[i].m_b * 255.0) );
        tgaImage.put ( (unsigned char) ( m_pixels[i].m_g * 255.0) );
        tgaImage.put ( (unsigned char) ( m_pixels[i].m_r * 255.0) );
        tgaImage.put ( (unsigned char) ( m_pixels[i].m_a * 255.0) );
    }
    tgaImage.close();
    return true;
}
//------------------------------------------------------------------------------
const Color& Image::Get ( uint32_t i_x, uint32_t i_y) const
{
    return m_pixels [ m_width * i_y + i_x ];
}
//------------------------------------------------------------------------------
void Image::Set ( uint32_t i_x, uint32_t i_y, const Color& i_value)
{
    m_pixels [ m_width * i_y + i_x ] = i_value;
}
}//end of namespace
