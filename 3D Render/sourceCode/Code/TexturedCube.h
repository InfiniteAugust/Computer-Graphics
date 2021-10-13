#pragma once
#include "Scene.h"

class TexturedCube{
public:
    TexturedCube(){};
    ~TexturedCube(){};
    TexturedCube(const std::string& filename);
    TexturedCube(const std::string& front, const std::string& left,const std::string& back,const std::string& right,const std::string& top,const std::string& bottom);
private:
    GLint texIDFront;
    GLint texIDBack;
    GLint texIDLeft;
    GLint texIDRight;
    GLint texIDTop;
    GLint texIDBottom;


};
