#ifndef VEC3_HPP
#define VEC3_HPP

#include <iostream>

class Vec3
{
public:
    Vec3(float x, float y, float z);
    Vec3() : Vec3(0.0f, 0.0f, 0.0f) {}

    inline float magnitude() const;

    // static methods
    static float dot(const Vec3& first, const Vec3& second);
    static Vec3 cross(const Vec3& first, const Vec3& second);
    static Vec3 normalize(const Vec3& vec3);
    static float distance(const Vec3& u, const Vec3& v);

    // operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Vec3& vec3);
    Vec3 operator+(Vec3 const &vec3) const;
    Vec3 operator-(Vec3 const &vec3) const;
    Vec3 operator*(Vec3 const &vec3) const;
    Vec3 operator/(float const scalar) const;
    Vec3 operator*(float const scalar) const;

    float x, y, z;

private:
};

#endif
