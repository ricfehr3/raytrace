#include "Mat44.hpp"

Mat44::Mat44()
{
    // Initialize to all zero, except x[3][3] = 1
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            x[i][j] = 0;
        }
    }
    x[3][3] = 1;
}


Mat44 Mat44::getRotation(const Vec3 &unitVec, const Vec3 &rotVec)
{
    // using Rodrigues' rotation formulat
    Mat44 res;
    Vec3 v = Vec3::cross(unitVec, rotVec);
    float cos = Vec3::dot(unitVec, rotVec);
    Mat44 id = Mat44::Identity;
    Mat44 vMat = Mat44::Zeroes;

    vMat.x[0][1] = -v.z;
    vMat.x[0][2] =  v.y;
    vMat.x[1][0] =  v.z;
    vMat.x[1][2] = -v.x;
    vMat.x[2][0] = -v.y;
    vMat.x[2][1] =  v.x;

    res = id + vMat + vMat*vMat*(1/(1+cos));
    
    return res;
}


Mat44 Mat44::makeIdentity()
{
    Mat44 res;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            if(i==j)
                res.x[i][j] = 1;
            else
                res.x[i][j] = 0;
        }
    }
    return res;
}


Mat44 Mat44::makeZeroes()
{
    Mat44 res;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            res.x[i][j] = 0;
        }
    }
    return res;
}


std::ostream& operator<<(std::ostream& os, const Mat44& mat44)
{
    for(int i=0; i<4; i++)
    {
        os << "x[" << i << "][0]=" << mat44.x[i][0]
           << " x[" << i << "][1]=" << mat44.x[i][1]
           << " x[" << i << "][2]=" << mat44.x[i][2]
           << " x[" << i << "][3]=" << mat44.x[i][3] << std::endl;
    }
    return os;
}


Mat44 Mat44::operator+(const Mat44 &mat44) const
{
    Mat44 res;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            res.x[i][j] = x[i][j] + mat44.x[i][j];
        }
    }
    return res;
}


Mat44 Mat44::operator*(const Mat44 &mat44) const
{
    Mat44 res;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            float sum = 0.0f;
            for(int k=0; k<4; k++)
            {
                sum += x[i][k] * mat44.x[k][j]; 
            }
            res.x[i][j] = sum;
        }
    }
    return res;
}


Vec3 Mat44::operator*(const Vec3 &vec3) const
{
    // Since I'm using a 4x4 for a 3x3, I'm going to just do multiplication here...
    Vec3 res;
    Mat44 vectorRepresentation = Mat44::Zeroes;
    vectorRepresentation.x[0][0] = vec3.x;
    vectorRepresentation.x[1][0] = vec3.y;
    vectorRepresentation.x[2][0] = vec3.z;

    Mat44* thisPtr = const_cast<Mat44*>(this);
    Mat44 matRes = (*thisPtr)*vectorRepresentation;

    res.x = matRes.x[0][0];
    res.y = matRes.x[1][0];
    res.z = matRes.x[2][0];

    return res;
}

    
Mat44 Mat44::operator*(const float scalar) const
{
    Mat44 res;
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            res.x[i][j] = scalar*x[i][j]; 
        }
    }
    return res;
}


const Mat44 Mat44::Zeroes = Mat44::makeZeroes(); 
const Mat44 Mat44::Identity = Mat44::makeIdentity(); 
