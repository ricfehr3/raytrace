#ifndef HITABLEOBJECT_HPP
#define HITABLEOBJECT_HPP

#include "SceneObject.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include "Material.hpp"

class HitableObject : public SceneObject
{
public:
    virtual bool testHit(const Ray& ray, Vec3& normal, float &distance) = 0;

    Material material; 

private:
};

#endif
