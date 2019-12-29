#ifndef VERTEX_HPP
#define VERTEX_HPP

#include "Vec3.hpp"

class Vertex
{
public:
    Vertex(Vec3 v, Vec3 vt, Vec3 vn);
    Vertex(Vec3 v, Vec3 vn);
    Vertex(Vec3 v);
    Vertex() : Vertex(Vec3(0.0f, 0.0f, 0.0f),
                      Vec3(0.0f, 0.0f, 0.0f),
                      Vec3(0.0f, 0.0f, 0.0f)) {}

    Vec3 v;
    Vec3 vt;
    Vec3 vn;
    
private:
};

#endif
