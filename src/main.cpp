#include <iostream>
#include <cmath>

#include "Vec3.hpp"
#include "Triangle.hpp"

double deg2rad (double degrees) {
        return degrees * 4.0 * atan (1.0) / 180.0;
}

int main() 
{
    Vec3 t_v0(0, 1, 5);
    Vec3 t_v1(1, -1, 5);
    Vec3 t_v2(-1, -1, 7);

    //std::cout << t_v0 - t_v1 << std::endl;
    //std::cout << t_v0/2 << std::endl;
    //std::cout << Vec3::normalize(t_v0) << std::endl;

    Triangle tri(t_v0, t_v1, t_v2);

    const unsigned int width = 640;
    const unsigned int height = 480;
    float fov = 51.52;
    float scale = tan(deg2rad(fov * 0.5));
    float imageAspectRatio = width/(float)height;

    std::cout << "P3\n" << width << " " << height << "\n255\n";

    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 -2 * (j + 0.5) / (float)height) * scale;
            Vec3 dir(x, y, -1);
            Vec3 orig(0, 0, 0);
            dir = Vec3::normalize(dir);
            float r;
            float g;
            float b;
            int ir;
            int ig;
            int ib;
            if(tri.testHit(orig, dir))
            {
                r = float(i) / float(width);
                g = float(j) / float(height);
                b = 0.2;
                ir = int(255.99*r);
                ig = int(255.99*g);
                ib = int(255.99*b);
            }
            else
            {
                ir = 0;
                ig = 0;
                ib = 0;
            }
            
            std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
}
