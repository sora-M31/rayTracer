#ifndef _IMAGE_H_
#define _IMAGE_H_

#include <vector>
#include "color.h"

namespace rayTracer
{
class Image
{
public:
    Image ( uint32_t i_width, uint32_t i_height);
    ~Image ();
    bool WriteTga ( char* i_fileName );
    //set
    Color& operator () ( uint32_t i_x, uint32_t i_y);
    ///access
    const Color& operator () ( uint32_t i_x, uint32_t i_y) const;
private:
    Image();
    uint32_t m_width;
    uint32_t m_height;
    std::vector< Color > m_pixels;
};//end of class
}//end of namespace
#endif //end of define
