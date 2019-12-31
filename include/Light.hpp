#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "Vec3.hpp"

class Light
{
public:
    Light();

    Vec3 color;
    Vec3 position;
    Vec3 direction;
    float intensity;

private:
};

#endif
