#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "Light.hpp"

class PointLight : public Light
{
public:
    PointLight();
    virtual void getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity, float &distance);

    float radius;
private:
};

#endif
