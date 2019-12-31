#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "Vertex.hpp"

class Triangle
{
public:
    Triangle(Vertex vert0, Vertex vert1, Vertex vert2);
    Triangle() : Triangle(Vertex(), Vertex(), Vertex()) {} 

    Vec3 normal() const;
    void calculateFlatNormals();
    bool testHit(const Vec3 &orig, const Vec3 &dir, Vec3 &normal, float &distance) const;

    Vertex vert[3];
private:
};

#endif
