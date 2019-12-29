#include "Vertex.hpp"


Vertex::Vertex(Vec3 v, Vec3 vt, Vec3 vn)
{
    this->v = v;
    this->vt = vt;
    this->vn = vn;
}


Vertex::Vertex(Vec3 v, Vec3 vn)
{
    this->v = v;
    this->vt = Vec3(0.0f, 0.0f, 0.0f);
    this->vn = vn;
}


Vertex::Vertex(Vec3 v)
{
    this->v = v;
    this->vt = Vec3(0.0f, 0.0f, 0.0f);
    this->vn = Vec3(0.0f, 0.0f, 0.0f);
}
