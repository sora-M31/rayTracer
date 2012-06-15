#include "objLoader.h"

namespace rayTracer
{
//------------------------------------------------------------------------------
bool ObjLoader::ParseFile ( const char* _fileName )
{
    std::ifstream fileIn;
    fileIn.open ( _fileName );
    std::string lineBuffer;
    if ( fileIn.is_open () )
    {
        while ( !fileIn.eof () )
        {
            //parse each line into a string
            getline ( fileIn, lineBuffer, '\n' );
            //parse string to tokens with delimiter
            StringList tokens;
            Tokenize (lineBuffer, " ", tokens);
            //put value in different array according to their type
            StringList::iterator iter = tokens.begin ();
            if ( iter!= tokens.end ())
            {
                if ( *iter == "v")
                {
                    tokens.pop_front ();
                    TokenToArray ( tokens, m_vertexBuffer );
                }
                else if  (*iter == "vn")
                {
                    tokens.pop_front ();
                    TokenToArray ( tokens, m_normalBuffer );
                }
                else if ( *iter == "vt")
                {
                    tokens.pop_front ();
                    TokenToArray ( tokens, m_textureBuffer );
                }
                else if ( *iter == "f")
                {
                    StringList faceToken;
                    for (++iter;iter!= tokens.end ();++iter)
                    {
                        Tokenize ( *iter, "/", faceToken );
                    }
                    TokenToArray ( faceToken, m_faceBuffer );
                }
            }
        }
        fileIn.close ();
        Serialize ();
        return true;
    }
    else
        return false;
}
//------------------------------------------------------------------------------
void ObjLoader::PrintLoadedInfo ()
{
    for (uint32_t i=0; i<m_vertexBuffer.size (); ++i)
    {
        if (i%3 ==2)
            std::cout<<m_vertexBuffer[i]<<" \n";
        else if (i%3 ==0)
            std::cout<<"v "<<m_vertexBuffer[i]<<" ";
        else
            std::cout<<m_vertexBuffer[i]<<" ";
    }
    for (uint32_t i=0; i<m_textureBuffer.size (); ++i)
    {
        if (i%2 ==1)
            std::cout<<m_textureBuffer[i]<<" \n";
        else
            std::cout<<"vt "<<m_textureBuffer[i]<<" ";
    }
    for (uint32_t i=0; i<m_normalBuffer.size (); ++i)
    {
        if ( i%3 ==2)
            std::cout<<m_normalBuffer[i]<<" \n";
        else if (i%3 ==0)
            std::cout<<"vn "<<m_normalBuffer[i]<<" ";
        else
            std::cout<<m_normalBuffer[i]<<" ";
    }
    for (uint32_t i=0; i<m_faceBuffer.size (); ++i)
    {
        if (i%9==8)
            std::cout<<m_faceBuffer[i]<<"\n";
        else if (i%9 ==0)
            std::cout<<"f "<<m_faceBuffer[i]<<"/";
        else if ( i%3 ==2)
            std::cout<<m_faceBuffer[i]<<" ";
        else
            std::cout<<m_faceBuffer[i]<<"/";
    }
}
//------------------------------------------------------------------------------
void ObjLoader::ClearData ()
{
    m_vertexBuffer.clear ();
    m_normalBuffer.clear ();
    m_textureBuffer.clear ();
    m_faceBuffer.clear ();
}
//------------------------------------------------------------------------------
void ObjLoader::TokenToArray ( const StringList& _tokens, std::vector<float>& o_array)
{
    StringList::const_iterator iter = _tokens.begin ();
    while ( iter!=_tokens.end () )
    {
        o_array.push_back ( atof (  (*iter).c_str () ) );
        ++iter;
    }
}
//------------------------------------------------------------------------------
/*from[http://oopweb.com/CPP/Documents/CPPHOWTO/Volume/C++Programming-HOWTO-7.html]*/
void ObjLoader::Tokenize ( const std::string& _str,
                           const std::string& _delimiters,
                           StringList& o_tokens )
{
    std::string::size_type lastPos = _str.find_first_not_of ( _delimiters, 0);
    std::string::size_type pos = _str.find_first_of ( _delimiters, lastPos);

    while ( pos != std::string::npos || lastPos != std::string::npos )
    {
        o_tokens.push_back ( _str.substr ( lastPos, pos-lastPos ) );
        lastPos = _str.find_first_not_of ( _delimiters,pos );
        pos = _str.find_first_of ( _delimiters, lastPos );
    }
}
//------------------------------------------------------------------------------
void ObjLoader::Serialize ()
{
    if ( m_textureBuffer.size ()!=0)
    {
        uint32_t size = m_faceBuffer.size ();
        for ( uint32_t i=0; i<size; i+=3)
        {
            //vertex
            uint32_t vertexIndex =  ( m_faceBuffer[i] -1)*3;
            m_vertexArray.push_back ( Vector (m_vertexBuffer[vertexIndex], m_vertexBuffer[vertexIndex+1], m_vertexBuffer[vertexIndex+2], 1.0f));
            //normal
            uint32_t normalIndex =  (m_faceBuffer[i+2]-1)*3;
            m_normalArray.push_back ( Vector (m_normalBuffer[normalIndex], m_normalBuffer[normalIndex+1], m_normalBuffer[normalIndex+2], 0.0f));
        }
    }
    else
    {
        std::cout<<"no texture\n";
        uint32_t size = m_faceBuffer.size ();
        for ( uint32_t i=0; i<size; i+=2)
        {
            //vertex
            uint32_t vertexIndex =  ( m_faceBuffer[i] -1)*3;
            //std::cout<<m_faceBuffer[i] -1<<" ";
//            std::cout<<vertexIndex<<" ";
//            std::cout<<vertexIndex+1<<" ";
//            std::cout<<vertexIndex+2<<"\n";
            m_vertexArray.push_back ( Vector (m_vertexBuffer[vertexIndex], m_vertexBuffer[vertexIndex+1], m_vertexBuffer[vertexIndex+2], 1.0f));
            //normal
            uint32_t normalIndex =  (m_faceBuffer[i+1]-1)*3;
            m_normalArray.push_back ( Vector (m_normalBuffer[normalIndex], m_normalBuffer[normalIndex+1], m_normalBuffer[normalIndex+2], 0.0f));
        }
    }
}
}//end of space
