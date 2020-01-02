#ifndef HITABLEOBJECT_HPP
#define HITABLEOBJECT_HPP

#include <memory>

#include "SceneObject.hpp"
#include "Ray.hpp"
#include "Vec3.hpp"
#include "Material.hpp"

// COULD IT BE! I finally found a real use for CRTP ^_^
class HitableObject : public SceneObject
{
public:
    virtual bool testHit(const Ray& ray, Vec3& normal, float &distance) = 0;
    virtual ~HitableObject() {};

    Material material; 

private:
};

#endif
