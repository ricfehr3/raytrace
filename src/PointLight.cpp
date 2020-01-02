#include <cmath>
#include "PointLight.hpp"


PointLight::PointLight()
{
    radius = 1.0f;
}

void PointLight::getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity)
{
    direction = this->direction - hitPoint;
    direction = Vec3::normalize(direction);
    intensity = this->intensity * this->color / (4 * M_PI * this->radius);
}
