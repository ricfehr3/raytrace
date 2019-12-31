#include <iostream>

#include "Triangle.hpp"


Triangle::Triangle(Vertex vert0, Vertex vert1, Vertex vert2)
{
    vert[0] = vert0;
    vert[1] = vert1;
    vert[2] = vert2;
}


Vec3 Triangle::normal() const
{
    Vec3 A = vert[1].v - vert[0].v;
    Vec3 B = vert[2].v - vert[0].v;
    Vec3 C = Vec3::cross(A, B);
    return Vec3::normalize(C);
}


void Triangle::calculateFlatNormals()
{
    Vec3 triNorm = normal();
    for(int i=0; i<3; i++)
    {
        vert[i].vn = triNorm;
    }
}
    

bool Triangle::testHit(const Vec3 &orig, const Vec3 &dir, Vec3 &normal, float &distance) const
{
    bool retVal = true;
    Vec3 E1vec = vert[1].v - vert[0].v;
    Vec3 E2vec = vert[2].v - vert[0].v;
    Vec3 Pvec = Vec3::cross(dir, E2vec);
    float det = Vec3::dot(Pvec, E1vec);
    float invDet = 1/det;
    Vec3 Tvec = orig - vert[0].v;
    Vec3 Qvec = Vec3::cross(Tvec, E1vec);

    float t = invDet*Vec3::dot(Qvec, E2vec);
    float u = invDet*Vec3::dot(Pvec, Tvec);
    float v = invDet*Vec3::dot(Qvec, dir);
    float w = 1 - u - v;

    if(u < 0 || u > 1)
        retVal = false;
    if(v < 0 || (u+v) > 1)
        retVal = false;

    if(retVal == true)
    {
        normal = vert[0].vn*w + vert[1].vn*u + vert[2].vn*v;
        normal = Vec3::normalize(normal);
        distance = t;
    }

    return retVal;
}
