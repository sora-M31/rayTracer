#include "math.h"
#include "texture.h"
#include "util.h"
namespace rayTracer
{
//------------------------------------------------------------------------------
Texture::Texture ()
: m_height(0),
  m_width(0),
  m_colors(0)
{}
//------------------------------------------------------------------------------
Texture::Texture ( uint32_t _height, uint32_t _width )
: m_height ( _height ),
  m_width ( _width ),
  m_colors ( m_height * m_width, Color ( 1,1,1,1) )
{}
//------------------------------------------------------------------------------
void Texture::MakeChecker()
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
            m_colors[ row * m_width + column ] = Color ( color, color, color, 1 );
		 }
	}
}
//------------------------------------------------------------------------------
const Color& Texture::GetColorBilinear( const Vector2D& _texCoord ) const
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

	if ( index >= m_colors.size() )
		index = m_colors.size() -1;
	else if ( index < 0 )
		index = 0;
	return m_colors [ index ];
}
}//end of namespace
