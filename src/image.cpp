#include "image.h"
#include <fstream>
#include "util.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
Image::Image( const std::string& _fileName )
{
	ReadFile( _fileName );
}
//------------------------------------------------------------------------------
Image::Image ( uint32_t _width, uint32_t _height, const Color& _color)
: m_width ( _width ),
  m_height( _height),
  m_pixels( _width * _height, _color )
{}
//------------------------------------------------------------------------------
Image::~Image ()
{}
//------------------------------------------------------------------------------
void Image::MakeChecker()
{
    //each black or white square with 8 rows and 8 columns, therefore 0x8
	//00 10 00 10
	//01 11 01 11
	//00 10 00 10
	//01 11 01 11
	uint32_t row,column,color;
	for( row=0; row < m_height;++row)
	{
		for( column=0; column < m_width; ++column)
		{
			color=( ( (row & 0x08) == 0 ) ^ ( (column & 0x08) == 0 ) );
            m_pixels[ row * m_width + column ] = Color ( color, color, color, 1 );
		 }
	}
}
//------------------------------------------------------------------------------
Color Image::GetColorBilinear( const Vector2D& _texCoord ) const
{
	/*
	   u->
	v    _ _ _ _ _ _
	|	|    _|_ _  |
	V	| 1 | |  2| |
		|_  |_|_ _|_|
		|   |_|_ _| |
		|  3  |  4  |
		|_ _ _|_ _ _|
	*/
	//from u v  get the four texel for sampling
	float u = _texCoord.u();
	float v = _texCoord.v();
	Clamp( u, 0, 1 );
	Clamp( v, 0, 1 );
	u *= m_width;
	v *= m_height;
	int ufloor = floor( u );
	int uceiling = ufloor +1;
	int vfloor = floor( v );
	int vceiling = vfloor +1;

	size_t index1 = (size_t) ( vfloor * m_width + ufloor);
	size_t index2 = (size_t) ( vfloor * m_width + uceiling);
	size_t index3 = (size_t) ( vceiling * m_width + ufloor);
	size_t index4 = (size_t) ( vceiling * m_width + uceiling);

	float weight1 = ( uceiling - u ) * ( vceiling - v );
	float weight2 = ( u + 1 - uceiling ) * ( vceiling - v );
	float weight3 = ( uceiling - u ) * ( v +1 - vceiling );
	float weight4 = ( u + 1 - uceiling ) * ( v +1 - vceiling );
	if ( index1 >= m_pixels.size() ) index1 = m_pixels.size() - 1;
	if ( index2 >= m_pixels.size() ) index1 = m_pixels.size() - 1;
	if ( index3 >= m_pixels.size() ) index1 = m_pixels.size() - 1;
	if ( index4 >= m_pixels.size() ) index1 = m_pixels.size() - 1;
	Color c = m_pixels[index1] * weight1 + m_pixels[index2] * weight2 + m_pixels[index3] * weight3 + m_pixels[index4] * weight4;
	return c;
}
//------------------------------------------------------------------------------
void Image::ReadFile(const std::string& _fileName)
{
    //get data from file to local array
    Magick::Image imageFile;
    imageFile.read(_fileName);
    imageFile.flip();
    m_width = imageFile.columns();
    m_height = imageFile.rows();
    uint8_t data[ m_width * m_height * 4 ];
    imageFile.write( 0, 0, m_width, m_height, "RGBA", Magick::CharPixel, data );
	uint32_t size = m_width * m_height * 4;
    m_pixels = std::vector<Color>(0);
	for( uint32_t i=0; i< size; i+=4 )
	{
		uint32_t index = i/4.0;
		if( index < m_width * m_height )
		m_pixels.push_back ( Color ( data[i]/255.0, data[i+1]/255.0, data[i+2]/255.0, data[i+3]/255.0 ) );
	}
}
//------------------------------------------------------------------------------
bool Image::WriteTga ( const std::string& _fileName )
{
    std::ofstream tgaImage ( _fileName.c_str(), std::ios_base::binary );

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
        //m_pixels[i].PrintColor();
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
	uint32_t index = m_width * _y + _x;
	assert( index < m_pixels.size() );
    return m_pixels [ index ];
}
//------------------------------------------------------------------------------
void Image::Set ( uint32_t _x, uint32_t _y, const Color& _value)
{
	uint32_t index = m_width * _y + _x;
	assert( index < m_pixels.size() );
    m_pixels [ index ] = _value;
}
}//end of namespace
