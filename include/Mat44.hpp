#ifndef MAT44_HPP
#define MAT44_HPP

#include <iostream>

#include "Vec3.hpp"

class Mat44
{
public:
    Mat44();

    // static methods
    static Mat44 getRotation(const Vec3 &unitVec, const Vec3 &rotVec);

    // operator overloading
    friend std::ostream& operator<<(std::ostream& os, const Mat44& mat44);
    Mat44 operator+(const Mat44 &mat44) const;
    Mat44 operator*(const Mat44 &mat44) const;
    Vec3 operator*(const Vec3 &vec3) const;
    Mat44 operator*(const float scalar) const;

    float x[4][4];

    // static variable
    static const Mat44 Identity;
    static const Mat44 Zeroes;

private:
    static Mat44 makeIdentity();
    static Mat44 makeZeroes();
};

#endif
