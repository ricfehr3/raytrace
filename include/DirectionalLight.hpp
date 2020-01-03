#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"

class DirectionalLight : public Light
{
public:
    DirectionalLight();
    virtual void getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity, float &distance);

private:
};

#endif
