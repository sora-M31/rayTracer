#ifndef _COLOR_H_
#define _COLOR_H_

namespace rayTracer
{
class Color
{
public:
    Color ();
    ~Color ();
    Color ( float _r, float _g, float _b, float _a );
    Color ( const Color& _other );
    Color operator +  ( const Color& _other );
    Color operator *  ( float _other );
    Color operator /  ( float _other );
    Color& operator =  ( const Color& _other );
    Color& operator +=  ( const Color& _other );
    Color& operator *=  ( float _other );
    Color& operator /=  ( float _other );
    inline const float& r() const { return m_data[0]; }
    inline float& r() { return m_data[0]; }
    inline const float& g() const { return m_data[1]; }
    inline float& g() { return m_data[1]; }
    inline const float& b() const { return m_data[2]; }
    inline float& b() { return m_data[2]; }
    inline const float& a() const { return m_data[3]; }
    inline float& a() { return m_data[3]; }
    void PrintColor();

private:
    float m_data[ 4 ];
};//end of class
}//end of namespace
#endif //end of define
