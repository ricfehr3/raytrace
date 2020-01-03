#ifndef MESH_HPP
#define MESH_HPP

#include <vector>
#include <memory>

#include "Triangle.hpp"
#include "Vec3.hpp"
#include "DirectionalLight.hpp"
#include "Ray.hpp"

class Mesh
{
public:
    std::vector<Triangle> tris; 

    bool testHit(const Ray &ray, Vec3 &normal, float &distance) const; 
    bool testHit(const Ray &ray, float &distance) const; 

private:
};

#endif
