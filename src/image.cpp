#include "image.h"
#include <fstream>
namespace rayTracer
{
//------------------------------------------------------------------------------
Image::Image ()
: m_width(0),
  m_height(0),
  m_pixels(0)
{}
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
const Color& Image::GetColorBilinear( const Vector2D& _texCoord ) const
{
#if 0
	if ( _u < 0.0) _u = -_u;
	if ( _v < 0.0) _v = -_v;

	Clamp( _u, 0, 1 );
	Clamp( _v, 0, 1 );
#endif

	//uint32_t column = floor( _u * m_width );
	int column = _texCoord.u() * m_width ;
	//uint32_t row = floor( _texCoord.v() * m_height );
	int row = _texCoord.v() * m_height;
	if ( column < 0 )
		column += m_width;
	if ( row < 0 )
		row += m_height;
	uint32_t index =  m_height * row + column;

	if ( index >= m_pixels.size() )
		index = m_pixels.size() -1;
	else if ( index < 0 )
		index = 0;
	return m_pixels [ index ];
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
		//std::cout<<size<<"\n";
		//std::cout<<m_width*m_height<<"\n";
		uint32_t index = i/4.0;
		//std::cout<<index<<"\n";
		if( index < m_width * m_height )
		m_pixels.push_back ( Color ( data[i]/255.0, data[i+1]/255.0, data[i+2]/255.0, data[i+3]/255.0 ) );
		//m_colors[index].PrintColor();
	}
    //imageFile.write( "output.png");
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
