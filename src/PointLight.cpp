#include <cmath>
#include "PointLight.hpp"


PointLight::PointLight()
{
    radius = 1.0f;
}

void PointLight::getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity, float &distance)
{
    direction = this->position - hitPoint;
    float r2 = direction.magnitude();
    distance = sqrt(r2);
    // normalize the incident light ray directions
    direction.x = direction.x / distance;
    direction.y = direction.y / distance;
    direction.z = direction.z / distance;
    intensity = this->intensity * this->color / (4 * M_PI * r2);
}
