#ifndef MESH_HPP
#define MESH_HPP

#include <vector>

#include "Triangle.hpp"
#include "Vec3.hpp"
#include "Light.hpp"

class Mesh
{
public:
    std::vector<Triangle> tris; 

    bool testHit(const Vec3 &origin, const Vec3 &direction, const Light &light, Vec3 &normal, Vec3 &color) const;

private:
};

#endif
