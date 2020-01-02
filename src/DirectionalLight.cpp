#include "DirectionalLight.hpp"

DirectionalLight::DirectionalLight()
{
}


void DirectionalLight::getDirectionAndIntensity(const Vec3 &hitPoint, Vec3 &direction, Vec3 &intensity)
{
   direction = this->direction; 
   intensity = this->intensity * color;
}
