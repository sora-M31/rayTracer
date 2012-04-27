#ifndef _COLOR_H_
#define _COLOR_H_

namespace rayTracer
{
class Color
{
public:
    Color ();
    ~Color ();
    Color ( float i_r, float i_g, float i_b, float i_a );
    Color ( const Color& i_other );
    Color operator +  ( const Color& i_other );
    Color operator *  ( float i_other );
    Color operator /  ( float i_other );
    Color& operator =  ( const Color& i_other );
    Color& operator +=  ( const Color& i_other );
    Color& operator *=  ( float i_other );
    Color& operator /=  ( float i_other );
    float r() const;
    float g() const;
    float b() const;
    float a() const;
    void PrintColor();
private:
    union
    {
        struct
        {
            float m_r;
            float m_g;
            float m_b;
            float m_a;
        };
        float m_data[ 4 ];
    };
};//end of class
}//end of namespace
#endif //end of define
