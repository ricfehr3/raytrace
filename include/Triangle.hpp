#include "Vec3.hpp"

class Triangle
{
public:
    Triangle(Vec3 v0, Vec3 v1, Vec3 v2);
    Triangle() : Triangle(Vec3( 0.0f,  1.0f,  0.0f),
                          Vec3( 1.0f, -1.0f,  0.0f),
                          Vec3(-1.0f, -1.0f,  0.0f)) {} 

    Vec3 normal() const;
    bool testHit(Vec3 orig, Vec3 dir);

    Vec3 v[3];
private:
};
