#include <limits>

#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight()
{
}


void DirectionalLight::getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity, float &distance)
{
   direction = this->direction; 
   intensity = this->intensity * color;
   distance = std::numeric_limits<float>::infinity();
}
