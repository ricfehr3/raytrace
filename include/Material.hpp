#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include "Color.hpp"

class Material
{
public:
    // Enum NEEDS to be declared before constructor
    enum Type
    {
        Diffuse,
        Metal
    };

    Material(Color albedo, Type type);
    Material() : Material(Color(0.0f, 0.0f, 0.0f), Type::Diffuse) {}

    Color albedo;
    Type type;

private:
};

#endif
