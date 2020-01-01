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

    //bool testHit(const Vec3 &origin, const Vec3 &direction, const DirectionalLight &light, Vec3 &normal, Vec3 &color) const;
    //bool testHit(const Vec3 &origin, const Vec3 &direction,  const std::unique_ptr<Light> &light, Vec3 &normal, Vec3 &color) const;
    bool testHit(const Ray &ray, const std::unique_ptr<Light> &light, Vec3 &normal, Vec3 &color) const;
    bool testHit(const Ray &ray, Vec3& normal, float &distance) const; 

private:
};

#endif
