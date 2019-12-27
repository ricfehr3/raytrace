#include <iostream>

#include "Triangle.hpp"


Triangle::Triangle(Vec3 v0, Vec3 v1, Vec3 v2)
{
    v[0] = v0;
    v[1] = v1;
    v[2] = v2;
}


Vec3 Triangle::normal() const
{
    Vec3 A = v[1] - v[0];
    Vec3 B = v[2] - v[0];
    Vec3 C = Vec3::cross(A, B);
    return Vec3::normalize(C);
}
    

bool Triangle::testHit(Vec3 orig, Vec3 dir)
{
    bool retVal = true;
    Vec3 E1vec = v[1] - v[0];
    Vec3 E2vec = v[2] - v[0];
    Vec3 Pvec = Vec3::cross(dir, E2vec);
    float det = Vec3::dot(Pvec, E1vec);
    float invDet = 1/det;
    Vec3 Tvec = orig - v[0];
    Vec3 Qvec = Vec3::cross(Tvec, E1vec);

    float t = invDet*Vec3::dot(Qvec, E2vec);
    float u = invDet*Vec3::dot(Pvec, Tvec);
    float v = invDet*Vec3::dot(Qvec, dir);

    if(u < 0 || u > 1)
        retVal = false;
    if(v < 0 || (u+v) > 1)
        retVal = false;

    //std::cout << "E1vec: "<< E1vec << "E2vec: "<< E2vec << std::endl;
    //std::cout << "u: "<< u << "v: "<< v << std::endl;

    return retVal;
}
