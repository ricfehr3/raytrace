#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "SceneObject.hpp"
#include "Vec3.hpp"

class Light : public SceneObject
{
public:
    Vec3 color;
    float intensity;
    virtual void getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity) = 0;

private:

};

#endif
