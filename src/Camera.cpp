#include "Camera.hpp"
#include "Vec3.hpp"

Camera::Camera(Vec3 origin, Vec3 direction, float zNear, float zFar)
{
    m_origin = origin;
    m_dir = direction;
    m_zNear = zNear;
    m_zFar = zFar;
}
