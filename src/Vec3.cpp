#include <cmath>

#include "Vec3.hpp"

Vec3::Vec3(float x, float y, float z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}


inline float Vec3::magnitude() const
{
    return sqrt(x*x + y*y + z*z);
}


float Vec3::dot(const Vec3& first, const Vec3& second)
{
    return first.x*second.x + first.y*second.y + first.z*second.z;
}


Vec3 Vec3::cross(const Vec3& first, const Vec3& second)
{
    float cx = first.y*second.z - first.z*second.y;
    float cy = first.z*second.x - first.x*second.z;
    float cz = first.x*second.y - first.y*second.x;

    return Vec3(cx, cy, cz);
}


Vec3 Vec3::normalize(const Vec3& vec3) 
{
    Vec3 res;
    float mag = vec3.magnitude();
    res = vec3/mag;
    return res;    
}

std::ostream& operator<<(std::ostream& os, const Vec3& vec3)
{
    os << "x:" << vec3.x << " y:" << vec3.y << " z:" << vec3.z;
    return os;
}


Vec3 Vec3::operator+(Vec3 const &vec3) const
{
    Vec3 res;
    res.x = x + vec3.x;
    res.y = y + vec3.y;
    res.z = z + vec3.z;
    return res;
}


Vec3 Vec3::operator-(Vec3 const &vec3) const
{
    Vec3 res;
    res.x = x - vec3.x;
    res.y = y - vec3.y;
    res.z = z - vec3.z;
    return res;
}
    

Vec3 Vec3::operator/(float const scalar) const
{
    Vec3 res; 
    res.x = x/scalar;
    res.y = y/scalar;
    res.z = z/scalar;
    return res; 
}


Vec3 Vec3::operator*(float const scalar) const
{
    Vec3 res; 
    res.x = x*scalar;
    res.y = y*scalar;
    res.z = z*scalar;
    return res; 
}
