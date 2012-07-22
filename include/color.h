#ifndef _COLOR_H_
#define _COLOR_H_

namespace rayTracer
{
class Color
{
public:
    Color ();
    ~Color ();
    Color ( float _r, float _g, float _b, float _a = 1.0f );
    Color ( const Color& _other );
    Color operator +  ( const Color& _other ) const ;
    Color operator *  ( float _other ) const ;
    Color operator /  ( float _other ) const ;
    Color& operator =  ( const Color& _other );
    Color& operator +=  ( const Color& _other );
    Color& operator *=  ( float _other );
    Color& operator /=  ( float _other );
    float& r() { return m_data[0]; }
    float& g() { return m_data[1]; }
    float& a() { return m_data[3]; }
    float& b() { return m_data[2]; }
    float r() const { return m_data[0]; }
    float g() const { return m_data[1]; }
    float b() const { return m_data[2]; }
    float a() const { return m_data[3]; }
    void PrintColor() const;
    void Clamp();

private:
    float m_data[ 4 ];
};//end of class
}//end of namespace
#endif //end of define
