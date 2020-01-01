#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"

class Material
{
public:
    Material(Color albedo);
    Material() : Material(Color(0.0f, 0.0f, 0.0f)) {}

    Color albedo;

private:
};

#endif
