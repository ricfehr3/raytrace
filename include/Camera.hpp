#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "Vec3.hpp"

class Camera
{
public:
    Camera(Vec3 origin, Vec3 direction, float zNear, float zFar);
    Camera() : Camera(Vec3(0.0f, 0.0f, 0.0f),
                      Vec3(0.0f, 0.0f, -1.0f),
                      0.1f,
                      100.0f) {}
private:
    float m_zNear;
    float m_zFar;
    Vec3 m_dir;
    Vec3 m_origin;
};

#endif
