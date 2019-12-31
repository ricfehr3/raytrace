#include "Camera.hpp"

Camera::Camera(Vec3 origin, Vec3 direction, float zNear, float zFar)
{
    m_origin = origin;
    m_dir = direction;
    m_zNear = zNear;
    m_zFar = zFar;

    calculateRotMat();
}


Ray Camera::castRay(const Vec3 &ray) const
{
    Ray res;
    Vec3 rotRay = m_rotMat*ray;
    res.origin = m_origin;
    res.direction = rotRay;

    return res;
}


void Camera::calculateRotMat()
{
    Vec3 worldVec(0.0f, 0.0f, -1.0f);
    Vec3 normalizeDir = Vec3::normalize(m_dir);

    m_rotMat = Mat44::getRotation(normalizeDir, worldVec);
}
