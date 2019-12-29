#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Triangle.hpp"
#include "Vec3.hpp"

class Mesh
{
public:
    std::vector<Triangle> tris; 

    bool testHit(Vec3 origin, Vec3 direction, Vec3 &normal, Vec3 &color);

private:
};

#endif
