#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
       
#include "OBJParser.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"
#include "Ray.hpp"

double deg2rad2 (double degrees) {
        return degrees * 4.0 * atan (1.0) / 180.0;
}

int main() 
{
    Mat44 test;

    int itr = 0;
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            test.x[i][j] = itr;
            itr++;
        }
    }

    std::cout << "testing mat44" << std::endl;
    std::cout << test*test << std::endl;
    std::cout << Mat44::Identity << std::endl;
    std::cout << test*Vec3(1,2,3) << std::endl;
        

    const unsigned int width = 640;
    const unsigned int height = 480;
    float fov = 51.52;
    float scale = tan(deg2rad2(fov * 0.5));
    float imageAspectRatio = width/(float)height;

    Mesh mesh;
    OBJParser::ParseMesh("man_scene.obj", mesh);
    std::cout << "From main... " << mesh.tris.size() << std::endl;
    std::cout << "tris v1 " << mesh.tris[0].vert[0].v << std::endl
              << "tris v2 " << mesh.tris[0].vert[1].v << std::endl
              << "tris v3 " << mesh.tris[0].vert[2].v << std::endl;

    std::ofstream outfile;
    outfile.open("test.ppm", std::ios::out | std::ios::trunc);

    outfile << "P3\n" << width << " " << height << "\n255\n";


    // CAMERA
    Vec3 camDir(0.5f, 0.5f, -1.0f);
    Camera cam(Vec3(2.0f, 2.0f, 0.0f), Vec3::normalize(camDir), 0.1, 100);

    auto t1 = std::chrono::high_resolution_clock::now();

    for(int j = 0; j < height; j++)
    {
        for(int i = 0; i < width; i++)
        {
            float x = (2 * (i + 0.5) / (float)width - 1) * imageAspectRatio * scale;
            float y = (1 - 2 * (j + 0.5) / (float)height) * scale;
            Vec3 dir(x, y, -1);
            Vec3 orig(0, 0, 0);
            dir = Vec3::normalize(dir);

            Ray ray = cam.castRay(dir);
            orig = ray.origin;
            dir = ray.direction;
            //std::cout << std::endl << dir << std::endl;
            //std::cout << ray.direction << std::endl;

            float r;
            float g;
            float b;
            int ir;
            int ig;
            int ib;

            ir = 0;
            ig = 0;
            ib = 128.0f;

            Vec3 color;
            Vec3 normal;
            mesh.testHit(orig, dir, normal, color);

            ir = color.x;
            ig = color.y;
            ib = color.z;

            outfile << ir << " " << ig << " " << ib << "\n";
        }
    }

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>( t2 - t1 ).count();

    std::cout << "damn, that took " << duration << " milliseconds!" << std::endl;

    outfile.close();
}
