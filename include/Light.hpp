#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "SceneObject.hpp"
#include "Vec3.hpp"

class Light : public SceneObject
{
public:
    Vec3 color;
    //Vec3 position;
    //Vec3 direction;
    float intensity;

private:

};

#endif
